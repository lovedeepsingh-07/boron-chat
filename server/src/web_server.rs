use crate::{command, server_state, error};
use axum::response::IntoResponse;
use boron_common::debug;
use std::sync::{Arc, RwLock};

#[derive(Debug, serde::Serialize, serde::Deserialize)]
struct LoginData {
    client_id: u64,
    username: String,
}

#[axum::debug_handler]
async fn login_route(
    axum::extract::State(state): axum::extract::State<Arc<RwLock<server_state::ServerState>>>,
    axum::extract::Json(login_data): axum::extract::Json<LoginData>,
) -> impl IntoResponse {
    let state = match state.read() {
        Ok(out) => out,
        Err(e) => {
            let err = error::Error::from(e);
            return (axum::http::StatusCode::INTERNAL_SERVER_ERROR, err.to_string()).into_response()
        }
    };
    let (reply_sender, reply_receiver) = crossbeam::channel::unbounded::<command::CommandReply>();

    match state
        .sender
        .send(command::Command::Login {
            client_id: login_data.client_id,
            username: login_data.username,
            reply_sender,
        }) {
            Ok(_) => {},
            Err(e) => {
                let err = error::Error::from(e);
                return (axum::http::StatusCode::INTERNAL_SERVER_ERROR, err.to_string()).into_response()
            }
    };

    match reply_receiver.recv() {
        Ok(reply) => {
            match reply {
                command::CommandReply::Login_Valid => {
                    return axum::http::StatusCode::OK.into_response();
                }
                command::CommandReply::Login_InvalidID => {
                    return (axum::http::StatusCode::CONFLICT, String::from("ID")).into_response();
                },
                command::CommandReply::Login_InvalidUsername => {
                    return (axum::http::StatusCode::CONFLICT, String::from("USERNAME")).into_response();
                },
            }
        }
        Err(e) => {
            debug::error(&format!("[ERROR] {}", e.to_string()));
        }
    };

    String::from("shit works!").into_response()
}

pub async fn run(state: Arc<RwLock<server_state::ServerState>>) -> Result<(), error::Error> {
    let router = axum::Router::new()
        .route("/login", axum::routing::post(login_route))
        .with_state(state);

    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await?;

    debug::debug("listening to incoming requests on :3000");
    axum::serve(listener, router).await?;
    Ok(())
}
