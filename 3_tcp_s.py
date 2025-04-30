import socket
# Create a TCP socket (SOCK_STREAM) using IPv4 (AF_INET)
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#set ip and port
server_ip = '' #listen to all available interfaces
server_port = 12345 #set port number
server.bind((server_ip, server_port)) #bind the socket to port
server.listen(5) #server can have up to five pending connections in queue

#infinit loop
while True:
    client_socket, client_address = server.accept() #accept new clients connection
    print('Connection from: ', client_address) #print ip and port
    data = client_socket.recv(1024) #recieve up to 1024 bytes from the client
    while not data.decode('utf-8') == '': #decode from unicode into bits
        print('Received: ', data.decode('utf-8')) #print message after decoding
        client_socket.send(data.upper()) #send the same data only uppercased now
        data = client_socket.recv(1024) #wait for next messafe

    print('Client disconnected') #print client disconnects
    client_socket.close() #close client socket