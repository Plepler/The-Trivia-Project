using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public static class Communicator
    {
        private static Socket socket;
        
        /// <summary>
        /// C'Tor for the class.
        /// Also creates the connection
        /// to the server.
        /// </summary>
        static Communicator()
        {
            int port = 24069;
            try
            {
                //Establish the remote endpoint
                //for the socket.
                IPHostEntry ipHost = Dns.GetHostEntry(Dns.GetHostName());
                IPAddress ipAddr = ipHost.AddressList[0];
                IPEndPoint localEndPoint = new IPEndPoint(ipAddr, port);

                //Creation TCP/IP Socket using
                //Socket class C'Tor
                socket = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);

                //Connect socket to remote endpoint
                socket.Connect(localEndPoint);
            }

            catch(SocketException se)
            {
                //Show pop message with error
                Error errPopup = new Error();
                errPopup.updateMessage("Socket Exception : " + se.ToString());
                errPopup.Show();
                System.Windows.Application.Current.Shutdown();//Close Application
            }


        }

        /// <summary>
        /// This function send a message to the server
        /// through the socket
        /// </summary>
        /// <param name="message"> The message that will be sent</param>
        public static void SendMessage(byte[] message)
        {
            int byteSent = socket.Send(message);
            if(byteSent < 3)
            {
                throw new Exception("Communication error with the server, couldn't send data");
            }
            
        }

        /// <summary>
        /// This function recieves a message from the server
        /// </summary>
        /// <returns> byte buffer(array) of the message </returns>
        public static byte[] recieveMessage()
        {
            byte[] message = new byte[1024];//Create buffer for message
            int bytesRecieved = socket.Receive(message);
            //Return only the used elements in the byte array
            return message.Take(bytesRecieved).ToArray();
        }
    }
}
