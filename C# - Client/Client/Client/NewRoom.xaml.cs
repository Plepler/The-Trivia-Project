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
    /// Interaction logic for NewRoom.xaml
    /// </summary>
    public partial class NewRoom : Window
    {
        public NewRoom()
        {
            InitializeComponent();
        }

        private void Reset_Click(object sender, RoutedEventArgs e)
        {
            textBoxName.Text = "";
            textBoxUsers.Text = "";
            textBoxQuestions.Text = "";
            textBoxTimer.Text = "";
        }

        private void Cancel_Click(object sender, RoutedEventArgs e)
        {
            Menu menu = new Menu();
            Close();
            menu.Show();
        }

        private void Submit_Click(object sender, RoutedEventArgs e)
        {
            if (IsValid())
            {
                string name = textBoxName.Text;
                uint users = uint.Parse(textBoxUsers.Text);
                uint questions = uint.Parse(textBoxUsers.Text);
                uint timer = uint.Parse(textBoxTimer.Text);

                // build register message and send it
                byte[] request = Serializer.SerializeRequest(new CreateRoomRequest(name, users, questions, timer));
                Communicator.SendMessage(request);

                //Recieve message
                byte[] serializedResponse = Communicator.recieveMessage();
                byte[] result = Helper.DisassembleResponse(serializedResponse);


                //Deserialize response according to CODE (first byte)
                if ((int)serializedResponse[0] == (int)CODES.ERROR)
                {
                    ErrorResponse errRes = Deserializer.DeserializeErrorResponse(result);
                    errormessage.Text = errRes.message;//Show error message
                }
                else if ((int)serializedResponse[0] == (int)CODES.CREATE)
                {
                    CreateRoomResponse createRoomRes = Deserializer.DeserializeCreateRoomResponse(result);
                    errormessage.Text = "You have successfully created a room.";
                }

            }
        }

        /// <summary>
        /// This function checks that all information in the boxes is valid
        /// </summary>
        /// <returns> True if all the input is valid </returns>
        private bool IsValid()
        {
            const int MAX_USERS = 10;
            const int MAX_QUESTIONS = 10;
            const int MAX_TIME = 100;

            if (textBoxName.Text.Length == 0 ||
                textBoxUsers.Text.Length == 0 ||
                textBoxQuestions.Text.Length == 0 ||
                textBoxTimer.Text.Length == 0)
            {
                errormessage.Text = "Please fill all boxes";
                return false;
            }

            int i;
            if (int.TryParse(textBoxUsers.Text, out i))
            {
                if(i > MAX_USERS)
                {
                    errormessage.Text = "Room is full";
                    return false;
                }
            }
            else
            {
                errormessage.Text = "Maximum users must be integer";
                return false;
            }

            if (int.TryParse(textBoxQuestions.Text, out i))
            {
                if (i > MAX_QUESTIONS)
                {
                    errormessage.Text = "Maximum 10 questions";
                    return false;
                }
            }
            else
            {
                errormessage.Text = "amount of questions must be integer";
                return false;
            }

            if (int.TryParse(textBoxTimer.Text, out i))
            {
                if (i > MAX_TIME)
                {
                    errormessage.Text = "Maximum 100 seconds";
                    return false;
                }
            }
            else
            {
                errormessage.Text = "Timer must be integer";
                return false;
            }

            return true;
        }


    }
}
