use bevy::prelude::*;

// Volumn setting
#[derive(Resource)]
pub struct Volume(pub u32);

impl Default for Volume {
    fn default() -> Self {
        Volume(0)
    }
}

// ScreenSize setting
#[derive(Resource)]
pub struct ScreenSize {
    x: usize,
    y: usize,
}

impl Default for ScreenSize {
    fn default() -> Self {
        ScreenSize { x: 1920, y: 1080 }
    }
}
