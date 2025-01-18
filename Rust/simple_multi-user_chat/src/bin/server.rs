use log::{error, info, warn};
use tokio::{
    io::{AsyncBufReadExt, AsyncWriteExt, BufReader},
    net::TcpListener,
    sync::broadcast,
};

#[tokio::main]
async fn main() {
    simple_logger::init().unwrap();
    info!("Starting server");

    let server_address = "localhost:8080";
    let server_listener = match TcpListener::bind(server_address).await {
        Ok(listener) => {
            info!("Listening on: {}", server_address);
            listener
        }
        Err(e) => {
            error!("Failed to bind to address: {}", e);
            return;
        }
    };

    let (tx, _rx) = broadcast::channel::<String>(10);

    tokio::spawn(async move {
        loop {
            let (mut client_socket, client_address) = match server_listener.accept().await {
                Ok((socket, address)) => {
                    info!("Accepted connection from: {}", address);
                    (socket, address)
                }
                Err(e) => {
                    error!("Failed to accept connection: {}", e);
                    continue;
                }
            };

            let tx = tx.clone();

            tokio::spawn(async move {
                let (mut client_reader, mut client_writer) = client_socket.split();

                let mut reader = BufReader::new(&mut client_reader);
                let mut line = String::new();

                let mut rx = tx.subscribe();

                loop {
                    match reader.read_line(&mut line).await {
                        Ok(0) => {
                            info!("Client disconnected: {}", client_address);
                            break;
                        }
                        Ok(_) => {
                            info!("{}: {:?}", client_address, line);
                            tx.send(line.clone()).unwrap();

                            let msg = rx.recv().await.unwrap();
                            client_writer.write_all(msg.as_bytes()).await.unwrap();
                        }
                        Err(e) => match e.kind() {
                            std::io::ErrorKind::ConnectionReset => {
                                warn!("Client connection reset: {}", client_address);
                                break;
                            }
                            _ => {
                                error!("Error: {:?}", e);
                                break;
                            }
                        },
                    }
                    line.clear();
                }
            });
        }
    });

    tokio::signal::ctrl_c().await.unwrap();
    info!("Received Ctrl-C signal, shutting down...");
}

// async fn main_loop(server_listener: TcpListener, tx: broadcast::Sender<String>) {}

// async fn handle_client(
//     mut client_socket: tokio::net::TcpStream,
//     client_address: std::net::SocketAddr,
//     tx: broadcast::Sender<String>,
// ) {
// }
