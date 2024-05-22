#[allow(unused)]
use bevy::prelude::*;

use crate::GameState;

#[derive(Default, Debug, States, Hash, Eq, PartialEq, Clone, Copy)]
enum MenuState {
    Main,
    Settings,
    #[default]
    Disabled, // not in menu, e.g. InGame state
}

// tag entities added on the Main menu screen
#[derive(Component)]
struct OnMenuMainScreen;

// tag entities added on the Settings menu screen
#[derive(Component)]
struct OnMenuSettings;

#[derive(Component)]
struct SelectedOption;

pub fn menu_plugin(app: &mut App) {
    app.init_state::<MenuState>()
        .add_systems(OnEnter(GameState::Menu), menu_setup)
        .add_systems(OnEnter(MenuState::Main), main_menu_setup);
}

fn menu_setup(mut menu_state: ResMut<NextState<MenuState>>) {
    info!("menu_setup: begin");
    menu_state.set(MenuState::Main); // This will queue up state transitions to be performed during the next frame update cycle.
    info!("menu_setup: done");
}

fn main_menu_setup() {
    info!("main_menu_setup: begin");
}
