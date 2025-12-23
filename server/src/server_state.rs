use crate::command;

#[derive(Debug)]
pub struct ServerState {
    pub sender: crossbeam::channel::Sender<command::Command>,
    pub receiver: crossbeam::channel::Receiver<command::Command>,
}
