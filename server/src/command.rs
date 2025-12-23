#[derive(Debug)]
pub enum Command {
    Login {
        client_id: u64,
        username: String,
        reply_sender: crossbeam::channel::Sender<CommandReply>
    },
}

#[allow(non_camel_case_types)]
#[derive(Debug)]
pub enum CommandReply {
    Login_Valid,
    Login_InvalidID,
    Login_InvalidUsername
}
