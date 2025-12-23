use crate::{server_state, command, error};
use std::{sync::{Arc, RwLock}, collections::{HashMap,HashSet}};

#[derive(Debug)]
struct ClientData {
    id: u64,
    username: String,
}
#[derive(Debug, Default)]
struct GameState {
    client_list: HashMap<u64, ClientData>,
    usernames_in_use: HashSet<String>,
}

fn handle_command(game_state: &mut GameState, cmd: command::Command) -> Result<(), error::Error> {
    match cmd {
        command::Command::Login { client_id, username, reply_sender } => {
            if !game_state.usernames_in_use.contains(&username) && !game_state.client_list.contains_key(&client_id) {
                game_state.client_list.insert(client_id, ClientData {id: client_id, username: username.clone() });
                game_state.usernames_in_use.insert(username);

                reply_sender.send(command::CommandReply::Login_Valid)?;
            } else if game_state.client_list.contains_key(&client_id) {
                reply_sender.send(command::CommandReply::Login_InvalidID)?;
            } else {
                reply_sender.send(command::CommandReply::Login_InvalidUsername)?;
            }
        }
    };
    Ok(())
}

pub fn run(state: Arc<RwLock<server_state::ServerState>>) -> Result<(), error::Error> {
    let state = state.read()?;
    let mut game_state = GameState::default();
    loop {
        match state.receiver.try_recv() {
            Ok(cmd) => handle_command(&mut game_state, cmd)?,
            Err(crossbeam::channel::TryRecvError::Empty) => {}
            Err(crossbeam::channel::TryRecvError::Disconnected) => {
                return Err(error::Error::ChannelReceiveError(String::from("failed to receive commands, channel is closed")));
            }
        }
    }
}
