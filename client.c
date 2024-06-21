// Mahny Barazandehtar - 20210702004 - CSE 331 - Section 4 - Bonus Exercise

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

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

// Function to connect to the server
int connect_to_server(char* servIP, unsigned short echoServPort) {
    int sock;
    struct sockaddr_in echoServAddr;

    // Create a socket for TCP connection
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    // Construct the server address structure
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

    // Establish the connection to the echo server
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    return sock;
}

int main(int argc, char *argv[]) {
    if ((argc < 2) || (argc > 3)) {
        fprintf(stderr, "Usage: %s <Server IP> [<Echo Port>]\n", argv[0]);
        exit(1);
    }

    char *servIP = argv[1];
    unsigned short echoServPort = (argc == 3) ? atoi(argv[2]) : 3333;
    int sock = connect_to_server(servIP, echoServPort);

    data sendData;
    sendData.sum = 0;

    // Seed the random number generator
    srand(time(0));

    // Fill the matrix with random numbers and calculate the sum
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            sendData.matrix[i][j] = rand() % 100;
            sendData.sum += sendData.matrix[i][j];
        }
    }

    // Send the data structure to the server
    if (send(sock, &sendData, sizeof(data), 0) != sizeof(data))
        DieWithError("send() sent a different number of bytes than expected");

    close(sock);
    return 0;
}
