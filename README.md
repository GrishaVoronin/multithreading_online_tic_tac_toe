# Multiplayer Tic-Tac-Toe Game in C++

This is a **multiplayer Tic-Tac-Toe game** built in C++. The game uses a **client-server architecture** where the server manages game logic and coordinates turns between two connected clients. Players connect to the server, send moves, and see both their moves and their opponent's in real-time.

## Overview

The **server** accepts incoming TCP connections, pairs clients into a game session, and orchestrates the game flow. The **game logic** resides entirely on the server side, ensuring that moves are processed correctly and game states are consistent between players. Each **client** connects to the server, sends moves, and receives updates about the game state.

### Key Features
- **Server-Managed Gameplay**: The server controls the game logic and state, ensuring accurate results and consistent game experience for both players.
- **Real-Time Interaction**: Players can see each other's moves instantly, allowing for an interactive gameplay experience.
- **Win/Loss Handling**: The server detects winning conditions and notifies both players of the outcome.

## How It Works

### Server

1. **Start-Up**: The server is started with a specified port, passed as a command-line argument.
2. **Connection Handling**:
   - When the first player connects, they receive a message to wait for an opponent.
   - Upon the second player’s connection, both players are notified that the game has started.
3. **Game Flow**:
   - The server sends the initial game board state and prompts the first player to make a move.
   - It then alternates between players, verifying each move’s validity, updating the game board, and checking for a win or draw condition.
   - Upon game completion, the server notifies both players of the result and disconnects them.

### Client

1. **Connection Setup**: The client connects to the server using the IP address and port specified as command-line arguments.
2. **Game Interaction**:
   - The client displays server messages in the console, including game status and board updates.
   - Players enter their moves, which the client sends to the server.
   - The client continually updates with the opponent’s moves, creating an interactive experience.

## How to Run

1. **Start the Server**:
   ```bash
   ./server --port <port_number>
   Replace <port_number> with the desired port for incoming connections.

2. **Start the Clients**: Each client connects using:
    ```bash
    ./client --connect <server_ip>:<port_number>
    Replace <server_ip> with the server’s IP address and <port_number> with the server’s listening port.
3 **Game Interaction**:
    Player 1 will wait for Player 2.
    Once both players are connected, the game begins with the server alternating turns between them until a win, draw, or disconnect occurs.
