use bevy::prelude::*;
use super::*;

pub fn spawn_hud(mut commands: Commands, asset_server: Res<AssetServer>, trace: Res<Trace>) {
    commands.spawn_bundle(UiCameraBundle::default());

    let top: f32 = 80.0;
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
                    font: asset_server.load("BodoniFLF-Roman.ttf"),
                    font_size: 27.0,
                    color: Color::hsl(0.0, 0.00, 0.20),
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

pub fn update_hud(
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