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
    /// Interaction logic for JoinRoom.xaml
    /// </summary>
    public partial class JoinRoom : Window
    {
        public JoinRoom()
        {
            InitializeComponent();

            List<Button> buttons = new List<Button>();

            //We are gonna create a button for each room

            // build register message and send it
            byte[] request = Serializer.SerializeRoomsRequest();
            Communicator.SendMessage(request);

            //Recieve message
            byte[] serializedResponse = Communicator.recieveMessage();
            byte[] result = Helper.DisassembleResponse(serializedResponse);


            //Deserialize response according to CODE (first byte)
            if ((int)serializedResponse[0] == (int)CODES.ERROR)
            {
                ErrorResponse errRes = Deserializer.DeserializeErrorResponse(result);
                //To Do: show error
            }
            else if ((int)serializedResponse[0] == (int)CODES.STATS)
            {
                GetRoomsResponse getRoomsRes = Deserializer.DeserializeGetRoomResponse(result);

                foreach (RoomData room in getRoomsRes.rooms)//Iterate over all rooms
                {
                    buttons.Add(new Button { ButtonContent = room.ToString(), ButtonID = (room.id).ToString(), data = room });
                }
            }

            ic.ItemsSource = buttons;
        }



    }

    class Button
    {
        public string ButtonContent { get; set; }
        public string ButtonID { get; set; }
        public RoomData data;
    }
}
