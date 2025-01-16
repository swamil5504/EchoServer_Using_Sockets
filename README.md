# EchoServer_Using_Sockets

This project implements a multithreaded Echo Server using C and socket programming. The server listens for incoming client connections and processes client messages, echoing a customized response back to the client. The implementation uses `pthread` for handling multiple clients simultaneously.

---

## Features

- Multithreaded server to handle multiple client connections.
- Socket programming for communication between server and clients.
- Lightweight and efficient implementation.
- Designed for testing and learning purposes.

---

## Requirements

- Linux operating system
- GCC compiler
- `lpthread` library for multithreading

---

## Files in the Project

1. **Server Code:** Implements the Echo Server.
2. **Client Code:** Implements the client logic for communicating with the server.

---

## How to Run

### Step 1: Save the Server Code
Save the server code into a file named `server.c`:

### Step 2: Save the Client Code
Save the client code into a file named `client.c`:

### Step 3: Compile the Server and Client
Run the following commands to compile the server and client:

```bash
gcc -o server server.c -lpthread
gcc -o client client.c
```

### Step 4: Run the Server
Start the server on your Linux machine:

```bash
./server
```

The server will begin listening on `127.0.0.1:9129`.

### Step 5: Run the Client
Open a new terminal and run the client:

```bash
./client
```

You can now interact with the server. Enter a name when prompted, and the server will respond with a customized message.

---

## Example Output

### Server Terminal:
```
Server waiting for connection...
Created new client thread
Input from client: John
```

### Client Terminal:
```
Enter your name: John
Server response: Thank you, John
```
