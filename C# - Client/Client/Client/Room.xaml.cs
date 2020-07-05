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
            this.data = data;
            refresh();
            InitializeComponent();   
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
                foreach (var player in players)
                {
                    players_list.Items.Add(player);
                }
            }
           
        }

        private void exit_room_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu();
            menu.Show();
            Close();
        }

        private void refresh(object sender, RoutedEventArgs e)
        {
            refresh();
        }

        private RoomData data;
    }
}
