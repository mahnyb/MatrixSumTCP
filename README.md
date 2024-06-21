# MatrixSumTCP

This project demonstrates a TCP client-server application where a client generates a 10x10 matrix of random integers, calculates the sum of the matrix elements, and sends the data to a server. The server, running indefinitely, receives and stores the matrix and its sum.

## Project Structure

### Server
- Runs indefinitely and listens for client connections on port 3333.
- Accepts incoming client connections and receives a data structure containing a 10x10 matrix and its sum.
- Processes and stores the received data.

### Client
- Generates a 10x10 matrix filled with random integers.
- Calculates the sum of the matrix elements.
- Creates a data structure containing the matrix and its sum.
- Connects to the server on port 3333 and sends the data structure.

## Compilation and Execution

Follow these steps to compile and run the server and client programs:

1. **Compile the Server and Client**

    Open two terminal tabs. In the first tab, compile the server:
    ```sh
    gcc server.c -o server
    ```

    In the second tab, compile the client:
    ```sh
    gcc client.c -o client
    ```

2. **Run the Server**

    In the server terminal tab, run the server on port 3333:
    ```sh
    ./server 3333
    ```

3. **Run the Client**

    In the client terminal tab, run the client, specifying the server IP (127.0.0.1) and port (3333):
    ```sh
    ./client 127.0.0.1 3333
    ```

