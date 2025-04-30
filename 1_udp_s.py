from socket import socket, AF_INET, SOCK_DGRAM

s = socket(AF_INET, SOCK_DGRAM)

src_ip = '' #listen to available interfaces
src_port = 12345 #set port number in order to connect the socket
s.bind((src_ip, src_port)) #connect the udp socket according to the port and ip

#opening server and run forever
while True:
    data, sender_info = s.recvfrom(2048) #recieve senders adress and also recieve up to 2048 bytes
    print(data.decode('utf-8')) #decode the message from unicode format
    print(sender_info) #print the data (servers ip and port)

    s.sendto(data.upper(), sender_info) #send to sender