#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

//main

int main() {

    //set ip and port
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    //create udp socket the same way we did in python 

    // Create a UDP socket (same as in Python: socket(AF_INET, SOCK_DGRAM))
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");  // If socket creation fails, print error
    }


    // Prepare sockaddr_in structure for destination address
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); //clear the structure with 0
    sin.sin_family = AF_INET; //use Ipv4
    sin.sin_addr.s_addr = inet_addr(ip_address); //Set Ip Adress
    sin.sin_port = htons(port_no); //Set port number
    

    //prepare message to send
    char data[] = "bye";
    int data_len = sizeof(data);

    //send message
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    //prepare to recieve message
    struct sockaddr_in from; //struct to store the senders ip
    unsigned int from_len = sizeof(struct sockaddr_in); //size of adress
    char buffer[4096]; //create buffer to hold the message

    //recieve message
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    //print response
    cout << "The server sent: " << buffer << endl;

    //close socket
    close(sock);

    return 0;
}