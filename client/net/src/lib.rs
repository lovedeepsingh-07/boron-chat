use std::io::Write;
use boron_common::debug;

#[allow(non_camel_case_types)]
#[cxx::bridge(namespace = "net")]
pub mod ffi {
    extern "Rust" {
        fn hello_client();
    }
}

pub fn hello_client() {
    debug::debug("Enter your username: ");
    std::io::stdout().flush().unwrap();
    let mut username = String::new();
    std::io::stdin().read_line(&mut username).unwrap();
    let username = username.trim().to_string();

    debug::info("login into http://127.0.0.1:3000/login...");
    let client_id = rand::random::<u64>();
    let res = match ureq::post("http://127.0.0.1:3000/login")
        .send_json(&serde_json::json!({"client_id": client_id, "username": username})){
            Ok(out) => out,
            Err(e) => {
                match e {
                    ureq::Error::StatusCode(status_code) => {
                        if status_code == 409 {
                            debug::error("sorry, username already in user");
                            return;
                        }
                    }
                    _ => {
                        debug::error(&format!("{}", e.to_string()))
                    }
                }
                return;
            }
        };
    debug::info(&format!("{:#?}", res));
}
