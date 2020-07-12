using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Client
{
    /// <summary>
    /// Interaction logic for Room.xaml
    /// </summary>
    public partial class Room : Window
    {
        private RoomData data;
        private bool isOpen;
        private bool isAdmin;

        public delegate void UpdateTextCallback(string message);
        
        private void UpdateAdminText(string message)
        {
            admin.Text = "ADMIN: " + message;
        }
        private void UpdateRoomNameText(string message)
        {
            room_name.Text = "ROOM NAME: " + message;
        }

        public delegate void updateListCallback(Queue<string> players);
        private void UpdatePLayersListText(Queue<string> players)
        {
            players_list.Items.Clear();
            foreach (var player in players)
            {
                players_list.Items.Add(player);
            }
        }

        public Room(RoomData data, bool isAdmin)
        {
            InitializeComponent();
            this.isAdmin = isAdmin;
            if (!isAdmin)
            {
                start.Visibility = Visibility.Hidden;
            }
            this.data = data;
            //If user is admin he was already added when creating the room
            if (!isAdmin) { addUserToRoom(); }
            Show();
            isOpen = true;
            Thread t = new Thread(Refresh);
            t.Start();
        }

        public void Refresh()
        {
            const int waitTime = 3000;//(Miliseconds)

            while (isOpen)
            {
                byte[] request = Serializer.SerializeRequest(new GetPlayersInRoomRequest(data.id));

                //send and recive message
                Helper.communicatorMutex.WaitOne();
                Communicator.SendMessage(request);
                byte[] serializedResponse = Communicator.recieveMessage();
                Helper.communicatorMutex.ReleaseMutex();
                
                byte[] result = Helper.DisassembleResponse(serializedResponse);


                //Deserialize response according to CODE (first byte)
                if ((int)serializedResponse[0] == (int)CODES.ERROR)
                {
                    ErrorResponse errRes = Deserializer.DeserializeErrorResponse(result);

                }
                else if ((int)serializedResponse[0] == (int)CODES.GET_PLAYER)
                {
                    GetPlayersInRoomResponse playersRes = Deserializer.DeserializeGetPlayersResponse(result);
                    Queue<string> players = playersRes.players;

                    //Update text blocks and list thorugh the thread
                    admin.Dispatcher.Invoke(new UpdateTextCallback(UpdateAdminText), new Object[] {players.Peek() });
                    room_name.Dispatcher.Invoke(new UpdateTextCallback(UpdateRoomNameText), new Object[] { data.name });
                    players_list.Dispatcher.Invoke(new updateListCallback(UpdatePLayersListText), new Object[] { players });

                }
                Thread.Sleep(waitTime);
            }
        }

        private void exit_room_Click(object sender, RoutedEventArgs e)
        {
            //In version v3.0.0 send leave room request for user
            //and delete room request for admin
            byte[] request = GetRequest(isAdmin);
            
            Helper.communicatorMutex.WaitOne();//Socket mutex on
            Communicator.SendMessage(request);
            byte[] serializedResponse = Communicator.recieveMessage();
            Helper.communicatorMutex.ReleaseMutex();//Socket mutex off

            //Get the response itself (without code and length)
            byte[] result = Helper.DisassembleResponse(serializedResponse);
            if (serializedResponse[0] == (int)CODES.ERROR)
            {
                ErrorResponse errRes = Deserializer.DeserializeErrorResponse(result);
                Error error = new Error();
                error.updateMessage(errRes.message);
                error.Show();
            }
            else
            {
                Menu menu = new Menu();
                menu.Show();
            }
            isOpen = false;
            Close();
        }
        private byte[] GetRequest(bool isAdmin)
        {
            byte[] request;
            if (isAdmin)
            {
                request = Serializer.SerializeCloseRoomRequest();
            }
            else
            {
                request = Serializer.SerializeLeaveRoomRequest();
            }
            return request;
        }

        /// <summary>
        /// This function adds the current user to the room
        /// </summary>
        public void addUserToRoom()
        {
            byte[] request = Serializer.SerializeRequest(new JoinRoomRequest(data.id));
            Helper.communicatorMutex.WaitOne();
            Communicator.SendMessage(request);
            byte[] serializedResponse = Communicator.recieveMessage();
            Helper.communicatorMutex.ReleaseMutex();
            byte[] result = Helper.DisassembleResponse(serializedResponse);

            //Deserialize response according to CODE (first byte)
            if ((int)serializedResponse[0] == (int)CODES.ERROR)
            {
                ErrorResponse errRes = Deserializer.DeserializeErrorResponse(result);
                Error error = new Error();
                error.updateMessage(errRes.message);
                error.Show();
            }
            else if ((int)serializedResponse[0] == (int)CODES.JOIN)
            {
                JoinRoomResponse joinRes = Deserializer.DeserializeJoinRoomResponse(result);
            }
        }


        private void Start_click(object sender, RoutedEventArgs e)
        {
            
        }
    }
}
