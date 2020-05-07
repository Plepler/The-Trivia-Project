import socket
import sys
import json

MSG_SIZE = 2048
SERVER_PORT = 42069
SERVER_IP = "127.0.0.1"
LOGIN = 100
SIGNUP = 101


def build_msg(type_msg):
    data = {}
    if type_msg == LOGIN:
        data["username"] = "user1"
        data["password"] = "1234"
        packet = LOGIN.to_bytes(1, byteorder='little')
        print(len(json.dumps(data)))
        packet += len(json.dumps(data)).to_bytes(4, byteorder='big')
        packet += json.dumps(data).encode('utf-8')
        return packet

    elif type_msg == SIGNUP:
        data["username"] = "user1"
        data["password"] = "1234"
        data["mail"] = "user1@gmail.com"
        packet = SIGNUP.to_bytes(1, byteorder='little')
        packet += len(json.dumps(data)).to_bytes(4, byteorder='big')
        packet += json.dumps(data).encode('utf-8')
        return packet


def send_request(sock):
    while True:
        choice = input("enter request, login / sign up / exit\n")
        if choice == "login":
            msg = build_msg(LOGIN)
            send_msg(sock, msg)
            return choice
            break

        elif choice == "sign up":
            msg = build_msg(SIGNUP)
            send_msg(sock, msg)
            return choice
            break

        elif choice == "exit":
            print("exit accomplished\n")
            return choice
            break
        else:
            print("try again, bad input")


def hello_handler(sock):
    # using function to get the answer of the server and print it
    server_msg = get_server_msg(sock)
    print(server_msg)
    client_msg = "hello"

    # send greeting
    send_msg(sock, client_msg)


def get_server_msg(sock):
    """
    the function gets a socket and get from the server its messege
    :param: sock: a socket that the user is useing
    :return: the messege from the server
    """
    # get message from socket, if it failed close socket and program
    try:
        msg = sock.recv(MSG_SIZE)

        if msg is bytes:
            msg = msg.decode()




    except Exception as e:
        print("ERORR:", e)
        sock.close()
        sys.exit()


# the function send msg to the server
# input: the socket and the request to send to the server
# output: NONE
def send_msg(sock, request):
    try:
        if type(request) == bytes:
            sock.sendall(request)
        else:
            sock.sendall(request.encode())
        print(request)
    except Exception as e:
        # if it failed close the socket and the program
        print("ERORR:", e)
        sock.close()
        sys.exit()


def main():
    # create socket with the server
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    # try to connect, if it failed print the error and close the program
    try:
        sock.connect(server_address)
    except Exception as e:
        print("ERROR:", e)
        sock.close()
        sys.exit()

    hello_handler(sock)
    while True:
        if send_request(sock) == "exit":
            break
        else:
            get_server_msg(sock)

    # close the socket
    sock.close()


if __name__ == '__main__':
    main()
