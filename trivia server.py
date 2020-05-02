import socket
import sys
MSG_SIZE = 2048
SERVER_PORT = 42069
SERVER_IP = "127.0.0.1"
def get_server_msg(sock):
    '''
    the function gets a socket and get from the server its messege
    :param: sock: a socket that the user is useing
    :return: the messege from the server
    '''
    #try to get it, if it failed close socket and program
    try:
        msg = sock.recv(MSG_SIZE)
        msg = msg.decode()
        return(msg)
    except Exception as e:
        print("ERORR:",e)
        sock.close()
        sys.exit()

#the function send msg to the server
#input: the socket and the request to send to the server
#output: NONE
def send_msg(sock, request):
    try:
        sock.sendall(request.encode())
    except Exception as e:
        #if it failed close the socket and the program
        print("ERORR:",e)
        sock.close()
        sys.exit()


def main():
    my_req = ' '#restart it so i can enter to the loop

    #create socket with the server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)

    #try to connect, if it failed print the error and close the program
    try:
        sock.connect(server_address)
    except Exception as e:
        print("ERORR:",e)
        sock.close()
        sys.exit()

    #using function to get the answer of the server and print it
    server_msg = get_server_msg(sock)
    print(server_msg)
    client_msg = input("enter yor request (hello) - ")
    #if its hello, send it and end the loop
    if (client_msg == "hello"):
        send_msg(sock, client_msg)
        print("client_msg = " + client_msg)
    else:
        print("bad request")

    #close the socket
    sock.close()
if __name__ == '__main__':
    main()
