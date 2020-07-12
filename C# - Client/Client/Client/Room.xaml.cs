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
        private bool IsOpen;
        public Room(RoomData data)
        {
            InitializeComponent();

            if (!isAdmin)
            {
                start.Visibility = Visibility.Hidden;
            }
            this.data = data;
            this.IsOpen = true;
            Thread t = new Thread(refresh);
            t.Start();
        }

        public void refresh()
        {
            while (IsOpen)
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
                    admin.Text = "ADMIN: " + players.Peek();
                    room_name.Text = "ROOM NAME: " + data.name;
                    players_list.Items.Clear();
                    foreach (var player in players)
                    {
                        players_list.Items.Add(player);
                    }
                }
                Show();
                Thread.Sleep(3000);
            }
        }

        private void exit_room_Click(object sender, RoutedEventArgs e)
        {
            //In version v3.0.0 send leave room request for user
            //and delete room request for admin
            byte[] request = GetRequest(isAdmin);
            
            Helper.communicatorMutex.WaitOne();
            Communicator.SendMessage(request);
            byte[] serializedResponse = Communicator.recieveMessage();
            Helper.communicatorMutex.ReleaseMutex();

            byte[] result = Helper.DisassembleResponse(serializedResponse);
            if ((int)serializedResponse[0] == (int)CODES.ERROR)
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
            this.IsOpen = false;
            Close();
        }
        private byte[] GetRequest(bool isAdmin)
        {
            byte[] request;
            if (isAdmin)
            {
                request = Serializer.SerializeCloseRoomResponse();
            }
            else
            {
                request = Serializer.SerializeLeaveRoomRequest();
            }
            return request;
        }

        public void addUserTorRoom()
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
        public bool isAdmin { set; get; }

        private void Start_click(object sender, RoutedEventArgs e)
        {

        }
    }
}
