#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    //set port number
    const int server_port = 5555;

    //create socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket (same as in Python: socket(AF_INET, SOCK_DGRAM))
    if (sock < 0) {
        perror("error creating socket"); //if socket didnt create print error
    }


    // Prepare sockaddr_in structure to define server address settings
    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin)); //set zeros

    sin.sin_family = AF_INET; //Ipv4
    sin.sin_addr.s_addr = INADDR_ANY; //Accept connections from any interface
    sin.sin_port = htons(server_port); //connect port to network byte order

    //Bind socket to ip
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }
    //prepare to recieve data
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];
    //recieve message from client
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }
    //print message recieved 
    cout << "The client sent: " << buffer << endl;
    //echo the message back to client 
    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }
    //close socket
    close(sock);

    return 0;
}