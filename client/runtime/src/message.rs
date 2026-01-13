use crate::{error, state};
use boron_common::{flatbuffers, packet};

pub fn poll_packets() -> Result<Vec<crate::ffi::MessageBytes>, error::Error> {
    let mut write_guard = state::CLIENT_STATE.write()?;
    let client_state = write_guard
        .as_mut()
        .ok_or(error::Error::StateNotInitializedError)?;

    let mut output: Vec<crate::ffi::MessageBytes> = Vec::new();
    while let Some(message) = client_state.client.receive_message(renet::DefaultChannel::ReliableOrdered) {
        output.push(crate::ffi::MessageBytes {
            data: message.to_vec(),
        });
    }
    return Ok(output);
}

pub fn send_message(input: String) -> Result<(), error::Error> {
    let mut write_guard = state::CLIENT_STATE.write()?;
    let client_state = write_guard
        .as_mut()
        .ok_or(error::Error::StateNotInitializedError)?;

    let mut builder = flatbuffers::FlatBufferBuilder::with_capacity(1024);
    let message_username = builder.create_string(client_state.username.as_str());
    let message_body = builder.create_string(input.as_str());
    let packet_data = packet::Message::create(
        &mut builder,
        &packet::MessageArgs {
            username: Some(message_username),
            body: Some(message_body),
        },
    );
    let packet = packet::Packet::create(
        &mut builder,
        &packet::PacketArgs {
            data_type: packet::Packet_Data::Message,
            data: Some(packet_data.as_union_value()),
        },
    );
    builder.finish(packet, None);
    let buf = builder.finished_data().to_vec();
    client_state.client.send_message(renet::DefaultChannel::ReliableOrdered, buf);
    Ok(())
}
