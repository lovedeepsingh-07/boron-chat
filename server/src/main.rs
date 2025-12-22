use axum::response::IntoResponse;
use boron_common::debug;

#[derive(Debug, serde::Serialize, serde::Deserialize)]
struct LoginData {
    client_id: u64,
    username: String,
}
#[axum::debug_handler]
async fn login_route(
    axum::extract::Json(login_data): axum::extract::Json<LoginData>,
) -> impl IntoResponse {
    println!("{:#?}", login_data);
    String::from("shit works!").into_response()
}

#[tokio::main]
async fn main() {
    let router = axum::Router::new()
        .route("/login", axum::routing::post(login_route));

    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000")
        .await
        .unwrap();

    debug::debug("listening to incoming requests on :3000");
    axum::serve(listener, router).await.unwrap();
}
