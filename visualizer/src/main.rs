use bevy::core::FixedTimestep;
use bevy::prelude::*;
mod hud;
mod parse;
mod update;

const WIDTH: f32 = 900.0;
const HEIGHT: f32 = 600.0;
const TIMESTEP: f64 = 5.0 / 60.0;
const BOARD_SIZE: f32 = HEIGHT - 40.0;

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
        .add_startup_system_to_stage(StartupStage::PreStartup, parse::parse_trace)
        .add_startup_system(spawn_camera.label("camera"))
        .add_startup_system(spawn_start.after("camera"))
        .add_startup_system(hud::spawn_hud)
        .add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(TIMESTEP))
                .with_system(next_turn),
        )
        .add_system(handle_input)
        .run()
}

fn spawn_camera(mut commands: Commands) {
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
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

    update::update_board(
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
            update::update_board(
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
        update::update_board(
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
        update::update_board(
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
        update::update_board(
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
            update::update_board(
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
pub struct Trace {
    pub first_player: String,
    pub second_player: String,
    pub boards: Vec<Vec<Vec<BoardCell>>>,
    pub width: f32,
    pub height: f32,
    pub side: f32,
}

#[derive(Debug)]
pub enum BoardCell {
    Empty,
    First,
    Second,
}

pub struct Turn(usize);

#[derive(Component)]
pub struct Cell;

pub struct Play(pub bool);

pub struct Speed(pub usize);

pub struct OnScreen(pub Vec<Vec<Option<Entity>>>);

#[derive(Component)]
pub struct TextTurn;

#[derive(Component)]
pub struct TextFirstPlayer;

#[derive(Component)]
pub struct TextSecondPlayer;

pub struct StartBoard(f32, f32);
