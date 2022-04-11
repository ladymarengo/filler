use bevy::prelude::*;
use regex::Regex;
use std::{env, fs::read_to_string};

const WIDTH: f32 = 800.0;
const HEIGHT: f32 = 600.0;

fn main() {
    App::new()
        .insert_resource(WindowDescriptor {
            title: "Filler Visualizer".to_string(),
            width: WIDTH,
            height: HEIGHT,
            ..Default::default()
        })
        .insert_resource(ClearColor(Color::ANTIQUE_WHITE))
        .add_plugins(DefaultPlugins)
        .add_system(bevy::input::system::exit_on_esc_system)
        .insert_resource(Trace {
            first_player: "".to_string(),
            second_player: "".to_string(),
            boards: Vec::new(),
            pieces: Vec::new(),
        })
        .add_startup_system(parse_trace)
        .run()
}

fn parse_trace(mut trace: ResMut<Trace>) {
    let args: Vec<String> = env::args().collect();
    let file = &args[1];

    let input: Vec<String> = read_to_string(file)
        .unwrap()
        .split("Plateau")
        .map(|l| l.to_string())
        .collect();

    let re = Regex::new(r"(?s).+/(.+).filler].+/(.+).filler.+").unwrap();
    let players = re.captures(&input[0]).unwrap();

    let mut boards: Vec<Vec<Vec<BoardCell>>> = Vec::new();
    let mut pieces: Vec<Vec<Vec<PieceCell>>> = Vec::new();

    for board in &input[1..] {
        let mut new_board: Vec<Vec<BoardCell>> = Vec::new();
        let mut new_piece: Vec<Vec<PieceCell>> = Vec::new();
        let parts: Vec<String> = board.split("Piece").map(|l| l.to_string()).collect();

        let board_rows: Vec<String> = parts[0].split('\n').map(|l| l.to_string()).collect();

        for row in board_rows {
            if row
                .chars()
                .any(|x| x == '.' || x == 'o' || x == 'O' || x == 'x' || x == 'X')
            {
                let mut new_row: Vec<BoardCell> = Vec::new();
                for c in row.chars() {
                    match c {
                        '.' => new_row.push(BoardCell::Empty),
                        'o' | 'O' => new_row.push(BoardCell::First),
                        'x' | 'X' => new_row.push(BoardCell::Second),
                        _ => (),
                    }
                }
                new_board.push(new_row);
            }
        }
        boards.push(new_board);

        let piece_rows: Vec<String> = parts[1].split('\n').map(|l| l.to_string()).collect();

        for row in piece_rows {
            if row.chars().any(|x| x == '.' || x == '*') {
                let mut new_row: Vec<PieceCell> = Vec::new();
                for c in row.chars() {
                    match c {
                        '.' => new_row.push(PieceCell::Empty),
                        '*' => new_row.push(PieceCell::Filled),
                        _ => (),
                    }
                }
                new_piece.push(new_row);
            }
        }
        pieces.push(new_piece);
    }

    trace.first_player = players.get(1).unwrap().as_str().to_string();
    trace.second_player = players.get(2).unwrap().as_str().to_string();
    trace.boards = boards;
    trace.pieces = pieces;
}

#[derive(Debug)]
struct Trace {
    first_player: String,
    second_player: String,
    boards: Vec<Vec<Vec<BoardCell>>>,
    pieces: Vec<Vec<Vec<PieceCell>>>,
}

#[derive(Debug)]
enum BoardCell {
    Empty,
    First,
    Second,
}

#[derive(Debug)]
enum PieceCell {
    Empty,
    Filled,
}
