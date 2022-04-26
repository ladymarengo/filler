use bevy::core::FixedTimestep;
use bevy::prelude::*;
use regex::Regex;
use std::{cmp::max, env, fs::read_to_string};

const WIDTH: f32 = 900.0;
const HEIGHT: f32 = 600.0;
const TIMESTEP: f64 = 5.0 / 60.0;
const BOARD_SIZE: f32 = HEIGHT - 40.0;

struct StartBoard(f32, f32);

fn main() {
    App::new()
        .insert_resource(WindowDescriptor {
            title: "Filler Visualizer".to_string(),
            width: WIDTH,
            height: HEIGHT,
            ..Default::default()
        })
        .insert_resource(ClearColor(Color::hsl(26.0, 0.32, 0.73)))
        .add_plugins(DefaultPlugins)
        .add_system(bevy::input::system::exit_on_esc_system)
        .insert_resource(Turn(0))
        .insert_resource(Play(false))
        .insert_resource(Speed(3))
        .insert_resource(OnScreen(Vec::new()))
        .add_startup_system_to_stage(StartupStage::PreStartup, parse_trace)
        .add_startup_system(spawn_camera.label("camera"))
        .add_startup_system(spawn_start.after("camera"))
        .add_startup_system(spawn_hud)
        .add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(TIMESTEP))
                .with_system(next_turn),
        )
        .add_system(handle_input)
        .run()
}

fn parse_trace(mut commands: Commands, mut onscreen: ResMut<OnScreen>) {
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
        pieces,
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

    commands.insert_resource(StartBoard(center_offset_x, (trace.height / 2.0)));
    commands.insert_resource(trace);
}

fn spawn_camera(mut commands: Commands) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
}

fn spawn_hud(mut commands: Commands, asset_server: Res<AssetServer>, trace: Res<Trace>) {
    commands.spawn_bundle(UiCameraBundle::default());

    let top: f32 = 120.0;
    let left: f32 = 610.0;

    commands
        .spawn_bundle(TextBundle {
            style: Style {
                align_self: AlignSelf::Auto,
                position_type: PositionType::Absolute,
                position: Rect {
                    top: Val::Px(top),
                    left: Val::Px(left),
                    ..Default::default()
                },
                ..Default::default()
            },
            text: Text::with_section(
                "Turn 0",
                TextStyle {
                    font: asset_server.load("BodoniFLF-Bold.ttf"),
                    font_size: 45.0,
                    color: Color::BLACK,
                },
                TextAlignment {
                    horizontal: HorizontalAlign::Center,
                    vertical: VerticalAlign::Center,
                    ..Default::default()
                },
            ),
            ..Default::default()
        })
        .insert(TextTurn);

    commands
        .spawn_bundle(TextBundle {
            style: Style {
                align_self: AlignSelf::Auto,
                position_type: PositionType::Absolute,
                position: Rect {
                    top: Val::Px(top + 70.0),
                    left: Val::Px(left),
                    ..Default::default()
                },
                ..Default::default()
            },
            text: Text::with_section(
                format!("{}: 1", trace.first_player),
                TextStyle {
                    font: asset_server.load("BodoniFLF-Bold.ttf"),
                    font_size: 40.0,
                    color: Color::hsl(216.0, 0.80, 0.40),
                },
                TextAlignment {
                    horizontal: HorizontalAlign::Center,
                    vertical: VerticalAlign::Center,
                    ..Default::default()
                },
            ),
            ..Default::default()
        })
        .insert(TextFirstPlayer);

    commands
        .spawn_bundle(TextBundle {
            style: Style {
                align_self: AlignSelf::Auto,
                position_type: PositionType::Absolute,
                position: Rect {
                    top: Val::Px(top + 110.0),
                    left: Val::Px(left),
                    ..Default::default()
                },
                ..Default::default()
            },
            text: Text::with_section(
                format!("{}: 1", trace.second_player),
                TextStyle {
                    font: asset_server.load("BodoniFLF-Bold.ttf"),
                    font_size: 40.0,
                    color: Color::hsl(0.0, 0.80, 0.40),
                },
                TextAlignment {
                    horizontal: HorizontalAlign::Center,
                    vertical: VerticalAlign::Center,
                    ..Default::default()
                },
            ),
            ..Default::default()
        })
        .insert(TextSecondPlayer);

    commands
        .spawn_bundle(TextBundle {
            style: Style {
                align_self: AlignSelf::Auto,
                position_type: PositionType::Absolute,
                position: Rect {
                    top: Val::Px(top + 200.0),
                    left: Val::Px(left),
                    ..Default::default()
                },
                ..Default::default()
            },
            text: Text::with_section(
                "Controls:\nSpace - play/pause\nS - start\nE - end\nUp - faster\nDown - slower\nRight - next turn\nLeft - previous turn",
                TextStyle {
                    font: asset_server.load("BodoniFLF-Bold.ttf"),
                    font_size: 25.0,
                    color: Color::hsl(0.0, 0.00, 0.30),
                },
                TextAlignment {
                    horizontal: HorizontalAlign::Left,
                    vertical: VerticalAlign::Top,
                    ..Default::default()
                },
            ),
            ..Default::default()
        });
}

fn update_hud(
    texts: &mut Query<(
        &mut Text,
        Option<&TextTurn>,
        Option<&TextFirstPlayer>,
        Option<&TextSecondPlayer>,
    )>,
    turn: usize,
    player1: &str,
    player2: &str,
    score1: usize,
    score2: usize,
) {
    for (mut text, if_turn, if_first, if_second) in texts.iter_mut() {
        if let Some(_t) = if_turn {
            text.sections[0].value = format!("Turn {}", turn);
        }
        if let Some(_t) = if_first {
            text.sections[0].value = format!("{}: {}", player1, score1);
        }
        if let Some(_t) = if_second {
            text.sections[0].value = format!("{}: {}", player2, score2);
        }
    }
}

fn update_board(
    turn: &mut ResMut<Turn>,
    commands: &mut Commands,
    trace: &Res<Trace>,
    onscreen: &mut ResMut<OnScreen>,
    start_board: &Res<StartBoard>,
    texts: &mut Query<(
        &mut Text,
        Option<&TextTurn>,
        Option<&TextFirstPlayer>,
        Option<&TextSecondPlayer>,
    )>,
) {
    let mut score1: usize = 0;
    let mut score2: usize = 0;

    let random_offset = || (rand::random::<f32>() - 0.5) / 5.0;
    let hued_blue = Color::hsl(216.0, 0.68 + random_offset(), 0.59 + random_offset());
    let hued_red = Color::hsl(0.0, 0.67 + random_offset(), 0.63 + random_offset());
    for (r, row) in trace.boards[turn.0].iter().enumerate() {
        for (c, col) in row.iter().enumerate() {
            match *col {
                BoardCell::First => score1 += 1,
                BoardCell::Second => score2 += 1,
                _ => (),
            };

            let color;

            if let Some(e) = onscreen.0[r][c] {
                if let BoardCell::Empty = col {
                    commands.entity(e).despawn();
                    onscreen.0[r][c] = None;
                }
                continue;
            }

            match *col {
                BoardCell::Empty => continue,
                BoardCell::First => color = hued_blue,
                BoardCell::Second => color = hued_red,
            };

            onscreen.0[r][c] = Some(
                commands
                    .spawn_bundle(SpriteBundle {
                        transform: Transform {
                            translation: Vec3::new(
                                start_board.0 + trace.side * c as f32 + trace.side / 2.0,
                                start_board.1 - trace.side * r as f32 - trace.side / 2.0,
                                0.0,
                            ),
                            scale: Vec3::new(trace.side, trace.side, 1.0),
                            ..Default::default()
                        },
                        sprite: Sprite {
                            color,
                            ..Default::default()
                        },
                        ..Default::default()
                    })
                    .insert(Cell)
                    .id(),
            );
        }
    }

    update_hud(
        texts,
        turn.0,
        &trace.first_player,
        &trace.second_player,
        score1,
        score2,
    );
}

fn spawn_start(
    mut turn: ResMut<Turn>,
    mut commands: Commands,
    trace: Res<Trace>,
    mut onscreen: ResMut<OnScreen>,
    start_board: Res<StartBoard>,
    mut text: Query<(
        &mut Text,
        Option<&TextTurn>,
        Option<&TextFirstPlayer>,
        Option<&TextSecondPlayer>,
    )>,
) {
    commands.spawn_bundle(SpriteBundle {
        transform: Transform {
            translation: Vec3::new(
                start_board.0 + trace.width / 2.0,
                start_board.1 - trace.height / 2.0,
                0.0,
            ),
            scale: Vec3::new(trace.width + 16.0, trace.height + 16.0, 0.0),
            ..Default::default()
        },
        sprite: Sprite {
            color: Color::hsl(26.0, 0.32, 0.65),
            ..Default::default()
        },
        ..Default::default()
    });

    commands.spawn_bundle(SpriteBundle {
        transform: Transform {
            translation: Vec3::new(
                start_board.0 + trace.width / 2.0,
                start_board.1 - trace.height / 2.0,
                0.0,
            ),
            scale: Vec3::new(trace.width + 6.0, trace.height + 6.0, 1.0),
            ..Default::default()
        },
        sprite: Sprite {
            color: Color::hsl(26.0, 0.25, 0.91),
            ..Default::default()
        },
        ..Default::default()
    });

    update_board(
        &mut turn,
        &mut commands,
        &trace,
        &mut onscreen,
        &start_board,
        &mut text,
    );
}

fn next_turn(
    play: Res<Play>,
    speed: Res<Speed>,
    mut turn: ResMut<Turn>,
    mut commands: Commands,
    trace: Res<Trace>,
    mut onscreen: ResMut<OnScreen>,
    start_board: Res<StartBoard>,
    mut text: Query<(
        &mut Text,
        Option<&TextTurn>,
        Option<&TextFirstPlayer>,
        Option<&TextSecondPlayer>,
    )>,
) {
    if play.0 {
        for _ in 0..speed.0 {
            if turn.0 + 1 < trace.boards.len() {
                turn.0 += 1;
            }
            update_board(
                &mut turn,
                &mut commands,
                &trace,
                &mut onscreen,
                &start_board,
                &mut text,
            );
        }
    }
}

fn handle_input(
    keys: Res<Input<KeyCode>>,
    mut play: ResMut<Play>,
    mut speed: ResMut<Speed>,
    mut turn: ResMut<Turn>,
    mut commands: Commands,
    trace: Res<Trace>,
    current: Query<Entity, With<Cell>>,
    mut onscreen: ResMut<OnScreen>,
    start_board: Res<StartBoard>,
    mut text: Query<(
        &mut Text,
        Option<&TextTurn>,
        Option<&TextFirstPlayer>,
        Option<&TextSecondPlayer>,
    )>,
) {
    if keys.just_pressed(KeyCode::Space) {
        match play.0 {
            true => play.0 = false,
            false => play.0 = true,
        }
    }
    if keys.just_pressed(KeyCode::Right) {
        play.0 = false;
        if turn.0 < trace.boards.len() - 1 {
            turn.0 += 1;
        }
        update_board(
            &mut turn,
            &mut commands,
            &trace,
            &mut onscreen,
            &start_board,
            &mut text,
        );
    }
    if keys.just_pressed(KeyCode::Left) {
        play.0 = false;
        if turn.0 > 0 {
            turn.0 -= 1;
        }
        update_board(
            &mut turn,
            &mut commands,
            &trace,
            &mut onscreen,
            &start_board,
            &mut text,
        );
    }
    if keys.just_pressed(KeyCode::S) {
        play.0 = false;
        turn.0 = 0;
        update_board(
            &mut turn,
            &mut commands,
            &trace,
            &mut onscreen,
            &start_board,
            &mut text,
        );
    }
    if keys.just_pressed(KeyCode::E) {
        play.0 = false;
        for t in turn.0..trace.boards.len() {
            turn.0 = t;
            update_board(
                &mut turn,
                &mut commands,
                &trace,
                &mut onscreen,
                &start_board,
                &mut text,
            );
        }
    }
    if keys.just_pressed(KeyCode::Up) {
        speed.0 += 1;
    }
    if keys.just_pressed(KeyCode::Down) {
        if speed.0 > 1 {
            speed.0 -= 1;
        }
    }
}

#[derive(Debug)]
struct Trace {
    first_player: String,
    second_player: String,
    boards: Vec<Vec<Vec<BoardCell>>>,
    pieces: Vec<Vec<Vec<PieceCell>>>,
    width: f32,
    height: f32,
    side: f32,
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

struct Play(bool);

struct Speed(usize);

struct OnScreen(Vec<Vec<Option<Entity>>>);

#[derive(Component)]
struct TextTurn;

#[derive(Component)]
struct TextFirstPlayer;

#[derive(Component)]
struct TextSecondPlayer;
