use bevy::core::FixedTimestep;
use bevy::prelude::*;
use regex::Regex;
use std::{env, fs::read_to_string};

const WIDTH: f32 = 800.0;
const HEIGHT: f32 = 600.0;
const START_BOARD: (f32, f32) = (-370.0, 270.0);
const END_BOARD: (f32, f32) = (HEIGHT / 2.0 - 30.0, HEIGHT / 2.0 - 30.0);
const TIMESTEP: f64 = 5.0 / 60.0;

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
        .insert_resource(Turn(0))
        .add_startup_system(parse_trace.label("parse"))
        .add_startup_system(spawn_camera.label("camera").after("parse"))
        .add_startup_system(update_screen.after("camera"))
		.add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(TIMESTEP))
                .with_system(next_turn)
		)
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

fn spawn_camera(mut commands: Commands) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
}

fn update_screen(
    turn: ResMut<Turn>,
    mut commands: Commands,
    old: Query<Entity, With<Cell>>,
    trace: Res<Trace>,
) {
    for e in old.iter() {
        commands.entity(e).despawn_recursive();
    }

    let side = (HEIGHT - 60.0) / trace.boards[0].len() as f32;
    // dbg!(trace.boards[0][0].len());
    // dbg!(trace.boards[0].len());
    for (r, row) in trace.boards[turn.0].iter().enumerate() {
        for (c, col) in row.iter().enumerate() {
            let color = match *col {
                BoardCell::Empty => Color::WHITE,
                BoardCell::First => Color::GREEN,
                BoardCell::Second => Color::BLUE,
            };
            // dbg!(START_BOARD.0 + side * c as f32);
            // dbg!(START_BOARD.1 - side * r as f32);
            commands
                .spawn_bundle(SpriteBundle {
                    transform: Transform {
                        translation: Vec3::new(
                            START_BOARD.0 + side * c as f32,
                            START_BOARD.1 - side * r as f32,
                            0.0,
                        ),
                        scale: Vec3::new(side, side, 1.0),
                        ..Default::default()
                    },
                    sprite: Sprite {
                        color: color,
                        ..Default::default()
                    },
                    ..Default::default()
                })
                .insert(Cell);
        }
    }
}

fn next_turn(
    mut turn: ResMut<Turn>,
    mut commands: Commands,
    trace: Res<Trace>,
    current: Query<Entity, With<Cell>>,
) {
	if turn.0 < trace.boards.len() - 1 {
		turn.0 += 1;
	} else {
		turn.0 = 0;
	}
	
	update_screen(turn, commands, current, trace);
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

struct Turn(usize);

#[derive(Component)]
struct Cell;
