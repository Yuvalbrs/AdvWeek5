#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    //set ip adress and port
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;
    // Create a TCP socket (SOCK_STREAM) using IPv4 (AF_INET)
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket"); //print error if socket failed
    }
    // Prepare sockaddr_in structure for destination address
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); // set the structure with 0 
    sin.sin_family = AF_INET; //Ipv4
    sin.sin_addr.s_addr = inet_addr(ip_address); //set ip
    sin.sin_port = htons(port_no); //set port
    //print error if fails to connect
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }
    //create a message and set data and decode to bytes
    char data_addr[] = "Hello Im a message After a change";
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);

    if (sent_bytes < 0) {
    // error
    }

    char buffer[4096]; //create buffer to hold up the message
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    if (read_bytes == 0) {
    // connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    else {
        cout << buffer;
    }
    //close socket
    close(sock);


    return 0;
}