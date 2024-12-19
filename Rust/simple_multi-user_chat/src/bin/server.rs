use colored::Colorize;
use std::collections::HashMap;
use std::io::{Read, Write};
use std::net::{SocketAddr, TcpListener, TcpStream};
use std::sync::mpsc::{channel, Receiver, Sender};
use std::sync::Arc;
use std::thread;
use std::time::{Duration, SystemTime};

const BAN_DURATION: Duration = Duration::from_secs(600);

enum Message {
    ClientConnected(Arc<TcpStream>),
    ClientDisconnected(Arc<TcpStream>),
    Message {
        connection: Arc<TcpStream>,
        message: Vec<u8>,
    },
}

struct Client {
    connection: Arc<TcpStream>,
    last_message: SystemTime,
    strike_count: u8,
}

fn server(messages: Receiver<Message>) {
    let mut clients = HashMap::<SocketAddr, Client>::new();
    let mut banned_clients = HashMap::<SocketAddr, Client>::new();
    loop {
        match messages.recv() {
            Ok(message) => match message {
                Message::ClientConnected(connection) => {
                    let address = connection.peer_addr().unwrap();
                    if let Some(banned_at) = banned_clients.get(&address) {
                        if banned_at.last_message.elapsed().unwrap() > BAN_DURATION {
                            banned_clients.remove(&address);
                            println!("{}: unbanned {address}", "INFO".green());
                        } else {
                            println!("{}: banned {address} tried connecting", "INFO".green());
                            continue;
                        }
                    }
                    clients.insert(
                        address,
                        Client {
                            connection: connection,
                            last_message: SystemTime::now(),
                            strike_count: 0,
                        },
                    );
                    println!("{}: {address}", "CONNECTED".green());
                }
                Message::ClientDisconnected(connection) => {
                    let address = connection.peer_addr().unwrap();
                    clients.remove(&address);
                    println!("{}: {address}", "DISCONNECTED".green());
                }
                Message::Message {
                    connection,
                    message,
                } => {
                    let address = connection.peer_addr().unwrap();
                    for (&client_address, client) in clients.iter() {
                        if client_address != address {
                            client.connection.as_ref().write(&message).unwrap();
                        }
                    }
                    println!(
                        "{} ({}): {}",
                        "MESSAGE".green(),
                        address,
                        String::from_utf8_lossy(&message)
                    );
                }
            },
            Err(e) => {
                eprintln!("{}: {e}", "ERROR".red());
            }
        }
    }
}

fn client(stream: Arc<TcpStream>, messages: Sender<Message>) {
    messages
        .send(Message::ClientConnected(stream.clone()))
        .unwrap();
    let mut read_buffer = vec![0u8; 64];
    loop {
        match stream.as_ref().read(&mut read_buffer) {
            Ok(size) => {
                messages
                    .send(Message::Message {
                        connection: stream.clone(),
                        message: read_buffer[0..size].to_vec(),
                    })
                    .unwrap();
            }
            Err(e) => {
                eprintln!("{}: {e}", "ERROR".red());
                messages
                    .send(Message::ClientDisconnected(stream.clone()))
                    .unwrap();
            }
        }
    }
}

fn main() {
    let address = "127.0.0.1:8080";
    let listener = TcpListener::bind(address).unwrap();
    println!("{}: listening to {address}", "INFO".green());

    let (sender, receiver) = channel();
    thread::spawn(move || server(receiver));

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                let stream = Arc::new(stream);
                let sender = sender.clone();
                thread::spawn(move || client(stream, sender));
            }
            Err(e) => {
                eprintln!("{}: {e}", "ERROR".red());
            }
        }
    }
}
