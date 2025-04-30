from socket import socket, AF_INET, SOCK_DGRAM

s = socket(AF_INET, SOCK_DGRAM) # Create a UDP socket using IPv4

dst_ip = '127.0.0.1' #set a destination IP adress
dst_port = 12345 #set a destination Port

s.sendto(b'Hello', (dst_ip,dst_port)) #Send a Udp packet with the message to the destination

data, sender_info = s.recvfrom(2048) #recieve senders adress and also recieve up to 2048 bytes
print(data.decode('utf-8')) #Decode the data from unicode format to bits and print
print(sender_info) #print senders ip adress and info

s.close() #close server client
