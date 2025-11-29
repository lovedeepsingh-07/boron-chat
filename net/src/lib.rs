pub mod client;
pub mod constants;
pub mod debug;
pub mod server;

use client::*;
use server::*;

#[cxx::bridge(namespace = "net")]
mod ffi {
    #[namespace = "net::server"]
    extern "Rust" {
        #[rust_name = "server_setup"]
        fn setup(port: u16);
        #[rust_name = "server_update"]
        fn update(delta_time_ms: u64);
        #[rust_name = "server_send_packets"]
        fn send_packets();
    }

    #[namespace = "net::client"]
    extern "Rust" {
        #[rust_name = "client_setup"]
        fn setup();
        #[rust_name = "client_is_connected"]
        fn is_connected() -> bool;
        #[rust_name = "client_is_connecting"]
        fn is_connecting() -> bool;
        #[rust_name = "client_connect"]
        fn connect(delta_time_ms: u64);
        #[rust_name = "client_update"]
        fn update(delta_time_ms: u64);
        #[rust_name = "client_poll_messages"]
        fn poll_messages() -> Vec<String>;
        #[rust_name = "client_send_message"]
        fn send_message(input: String);
        #[rust_name = "client_send_packets"]
        fn send_packets();
    }
}
