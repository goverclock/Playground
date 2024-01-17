use bevy::prelude::*;

pub const BALL_COLOR: Color = Color::rgb(0f32, 178f32 / 255f32, 225f32 / 255f32);
pub const BALL_STARTING_POSITION: Vec3 = Vec3::new(0.0, -50.0, 1.0);
pub const BALL_SIZE: Vec3 = Vec3::new(30.0, 30.0, 0.0);
pub const BALL_SPEED: f32 = 400.0;
pub const INITIAL_BALL_DIRECTION: Vec2 = Vec2::new(0.5, -0.5);
