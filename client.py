import socket
import sys
import json

TYPE_INDEX = 0
SIZE_OF_DATA_TYPE = 1
SIZE_OF_DATA_LENGTH = 4
START_LENGTH_INDEX = 1
END_LENGTH_INDEX = 5
MSG_SIZE = 2048
SERVER_PORT = 42069
SERVER_IP = "127.0.0.1"
LOGIN = 100
SIGNUP = 101


def decoder(sock, msg):
    """
    the function decode the binary messeges into dictionary based on the protocol
    :param sock: the socket of the connection
    :param msg: the msg to decode
    :return: dictionary that holds the decoded data
    """
    # decode the type of the msg
    data_dict = {"type": str(msg[TYPE_INDEX])}

    # decode the len of the msg
    len = int.from_bytes(msg[START_LENGTH_INDEX: END_LENGTH_INDEX], byteorder='big')

    # receive the remaining data and create keys in the dict
    msg = sock.recv(len)
    data_dict["len"] = len
    data_dict["data"] = msg.decode()

    # format the msg in a string
    server_msg = data_dict["type"] + str(data_dict["len"]) + data_dict["data"]
    return server_msg


def build_msg(type_msg):
    """
    the function builed msg in the protocol format
    :param type_msg: the type of the msg (login || sign up)
    :return: the builded packet
    """
    data = {}  # declear

    if type_msg == LOGIN:
        # create keys with values
        data["username"] = input("enter your username: ")
        data["password"] = input("enter your password: ")

        # convert it to bytes
        packet = LOGIN.to_bytes(SIZE_OF_DATA_TYPE, byteorder='little')
        packet += len(json.dumps(data)).to_bytes(SIZE_OF_DATA_LENGTH, byteorder='little')
        packet += json.dumps(data).encode('utf-8')
        return packet

    elif type_msg == SIGNUP:
        # create keys with values
        data["username"] = input("enter your username: ")
        data["password"] = input("enter your password: ")
        data["email"] = input("enter your email: ")
        # convert it to bytes
        packet = SIGNUP.to_bytes(SIZE_OF_DATA_TYPE, byteorder='little')
        packet += len(json.dumps(data)).to_bytes(SIZE_OF_DATA_LENGTH, byteorder='little')
        packet += json.dumps(data).encode('utf-8')
        return packet


def send_request(sock):
    """
    the function send the request based on user desition
    :param sock: the socket
    :return: the request
    """
    while True:
        # get the wanted request from the user
        choice = input("enter request, login / sign up / exit\n")

        # based on user desition, builed the msg and send it
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

        # if the user asked for exit, print msg to the user and return the choice.
        elif choice == "exit":
            print("exit accomplished\n")
            return choice
            break
        else:
            print("try again, bad input")


def hello_handler(sock):
    # using function to get the answer of the server and print it
    server_msg = sock.recv(SIZE_OF_DATA_TYPE + SIZE_OF_DATA_LENGTH).decode()
    client_msg = "hello"

    # send greeting
    try:
        sock.sendall(client_msg.encode())
    except Exception as e:
        print("ERORR:", e)
        sock.close()
        sys.exit()


def get_server_msg(sock):
    """
    the function gets a socket and get from the server its messege
    :param: sock: a socket that the user is useing
    :return: the messege from the server
    """

    # get message from socket, if it failed close socket and program
    try:

        msg = sock.recv(SIZE_OF_DATA_TYPE + SIZE_OF_DATA_LENGTH)
        msg = decoder(sock, msg)
        return msg

    except Exception as e:
        print("ERORR:", e)
        sock.close()
        sys.exit()


def send_msg(sock, request):
    """
    the function send msg to the server
    :param sock: the socket
    :param request: the request to send to the server
    :return: NONE
    """
    try:
        sock.sendall(request)
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
            print("the answer is: " + get_server_msg(sock))

    # close the socket
    sock.close()


if __name__ == '__main__':
    main()
