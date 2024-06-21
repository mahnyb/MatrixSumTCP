// Mahny Barazandehtar - 20210702004 - CSE 331 - Section 4 - Bonus Exercise

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5
#define RCVBUFSIZE 32

// Structure to hold matrix and its sum
typedef struct data {
    int matrix[10][10];
    int sum;
} data;

// Function to handle errors
void DieWithError(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}

// Function to initialize server socket
int initializeServerSocket(unsigned short port) {
    int servSock;
    struct sockaddr_in echoServAddr;

    // Create socket for incoming connections
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    // Construct local address structure
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(port);

    // Bind to the local address
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    // Mark the socket to listen for incoming connections
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    return servSock;
}

// Function to accept client connections
int acceptClient(int servSock) {
    int clntSock;
    struct sockaddr_in echoClntAddr;
    unsigned int clntLen = sizeof(echoClntAddr);

    // Accept an incoming connection
    if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
        DieWithError("accept() failed");

    return clntSock;
}

// Function to handle communication with the client
void HandleTCPClient(int clntSocket) {
    data receivedData;

    // Receive data from the client
    if (recv(clntSocket, &receivedData, sizeof(data), 0) <= 0) {
        close(clntSocket);
        return;
    }

    // Print the received matrix and sum
    printf("Received Matrix:\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", receivedData.matrix[i][j]);
        }
        printf("\n");
    }
    printf("Sum: %d\n", receivedData.sum);

    close(clntSocket);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    unsigned short echoServPort = atoi(argv[1]);
    int servSock = initializeServerSocket(echoServPort);

    // Run indefinitely to accept and handle client connections
    for (;;) {
        int clntSock = acceptClient(servSock);
        HandleTCPClient(clntSock);
    }

    return 0;
}
