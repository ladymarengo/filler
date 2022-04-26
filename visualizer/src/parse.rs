use bevy::prelude::*;
use super::*;
use regex::Regex;
use std::{env, fs::read_to_string};

pub fn parse_trace(mut commands: Commands, mut onscreen: ResMut<OnScreen>) {
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

    for board in &input[1..] {
        let mut new_board: Vec<Vec<BoardCell>> = Vec::new();
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
    }

    let board_width = boards[0][0].len() as f32;
    let board_height = boards[0].len() as f32;
    let side;
    let final_width;
    let final_height;

    if board_width > board_height {
        final_width = BOARD_SIZE;
        side = BOARD_SIZE / board_width;
        final_height = board_height * side;
    } else {
        final_height = BOARD_SIZE;
        side = BOARD_SIZE / board_height;
        final_width = board_width * side;
    }

    let trace = Trace {
        first_player: players.get(1).unwrap().as_str().to_string(),
        second_player: players.get(2).unwrap().as_str().to_string(),
        boards,
        width: final_width,
        height: final_height,
        side,
    };

    for _i in 0..trace.boards[0].len() {
        let mut new = Vec::new();
        for _j in 0..trace.boards[0][0].len() {
            new.push(None);
        }
        onscreen.0.push(new);
    }

    let center_offset_x = -(WIDTH - HEIGHT) / 2.0 - trace.width / 2.0;

    commands.insert_resource(StartBoard(center_offset_x, trace.height / 2.0));
    commands.insert_resource(trace);
}
