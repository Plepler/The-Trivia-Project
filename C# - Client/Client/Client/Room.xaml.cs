using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
        public Room(RoomData data)
        {
            InitializeComponent();
            if (!isAdmin)
            {
                start.Visibility = Visibility.Hidden;
            }
            this.data = data;
        }

        public void refresh()
        {
            byte[] request = Serializer.SerializeRequest(new GetPlayersInRoomRequest(data.id));
            Communicator.SendMessage(request);

            //Recieve message
            byte[] serializedResponse = Communicator.recieveMessage();
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
        }

        private void exit_room_Click(object sender, RoutedEventArgs e)
        {
            //In version v3.0.0 send leave room request for user
            //and delete room request for admin
            byte[] request = GetRequest(isAdmin);
            Communicator.SendMessage(request);
            byte[] serializedResponse = Communicator.recieveMessage();
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
        private void refresh(object sender, RoutedEventArgs e)
        {
            refresh();
        }

        public void addUserTorRoom()
        {
            byte[] request = Serializer.SerializeRequest(new JoinRoomRequest(data.id));
            Communicator.SendMessage(request);

            //Recieve message
            byte[] serializedResponse = Communicator.recieveMessage();
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

        private RoomData data;
        public bool isAdmin { set; get; }

        private void Start_click(object sender, RoutedEventArgs e)
        {

        }
    }
}
