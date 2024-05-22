use bevy::prelude::*;

mod settings;
use settings::*;

mod menu;
use menu::*;

#[derive(Default, Debug, States, Hash, Eq, PartialEq, Clone, Copy)]
enum GameState {
    #[default]
    Menu,
    InGame,
}

fn main() {
    App::new()
        .add_plugins(DefaultPlugins)
        .add_plugins(menu_plugin)
        .init_state::<GameState>()
        .init_resource::<ScreenSize>() // setting
        .init_resource::<Volume>() // setting
        .add_systems(Startup, setup)
        .run();
}

fn setup(mut game_state: ResMut<NextState<GameState>>, mut cmds: Commands) {
    info!("setup: begin");
    game_state.set(GameState::Menu); // TODO: remove
    cmds.spawn(Camera2dBundle {
        camera: Camera {
            clear_color: ClearColorConfig::Custom(Color::rgb(0.0, 0.0, 0.0)),
            ..Default::default()
        },
        ..Default::default()
    }); // there's no Camera2d in DefaultPlugins

    info!("setup: done");
}
