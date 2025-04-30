import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) # Create a TCP socket (SOCK_STREAM) using IPv4 (AF_INET)
dest_ip = '127.0.0.1' #set ip (local host)
dest_port = 12345 #set port
s.connect((dest_ip, dest_port)) #establish tcp connection with the server


msg = input("Message to send: ") #set input to send
#loop until user types in "quit"
while not msg == 'quit':
    s.send(bytes(msg, 'utf-8'))           # Send the message encoded as UTF-8 bytes
    data = s.recv(4096)                   # Wait and receive up to 4096 bytes from server
    print("Server sent: ", data.decode('utf-8'))  # decode and print server's response
    msg = input("Message to send: ")      # prompt for next message

s.close() #close socket