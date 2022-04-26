use bevy::prelude::*;
use super::*;

pub fn update_board(
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

    hud::update_hud(
        texts,
        turn.0,
        &trace.first_player,
        &trace.second_player,
        score1,
        score2,
    );
}