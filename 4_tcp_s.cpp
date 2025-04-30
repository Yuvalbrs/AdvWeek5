#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
    //set port number for server
    const int server_port = 5555;

    // Create a UDP socket (same as in Python: socket(AF_INET, SOCK_DGRAM))
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket"); //if fails print error
    }
    //prepare a struct in order to define serer adress settings
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); //set structure to 0s
    sin.sin_family = AF_INET; //Ipv4
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);
    //bind socket to struct ,if binding failed print error
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
    }
    //listen to socket with up to 5 pending connections in queue if failed print error
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
    }
    //prepare the struct to hold the message
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);
    //if building failed print error
    if (client_sock < 0) {
        perror("error accepting client");
    }
    //prepare buffer to hold the message
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
    // connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    //print buffer
    else {
        cout << buffer;
    }
    //send up the message in bytes
    int sent_bytes = send(client_sock, buffer, read_bytes, 0);
    //if failed print error
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
    //closing client and socket after message has been sent
    close(client_sock);
    close(sock);


    return 0;
}