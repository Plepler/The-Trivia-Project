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
    /// Interaction logic for Menu.xaml
    /// </summary>
    public partial class Menu : Window
    {
        private string username;

        public Menu()
        {
            InitializeComponent();
        }

        public void SetUsername(string username)
        {
            this.username = username;
        }

        private void LogOut_Click(object sender, RoutedEventArgs e)
        {
            {
                //Build signout request
                byte[] request = new byte[5];
                request[0] = (int)CODES.LOGOUT;
                System.Buffer.BlockCopy(Serializer.itob(0), 0, request, 1, 4);
                Communicator.SendMessage(request);

                byte[] response = new byte[1024];
                response = Communicator.recieveMessage();

                if ((int)response[0] == (int)CODES.LOGOUT)//Succesfully logged out
                {
                    //change windows to welcoming page
                    Close();
                    Welcome welcome = new Welcome();
                    welcome.Show();
                }
                else//Show error pop up
                {
                    //Change windows to error pop up
                    ErrorResponse errRes = Deserializer.DeserializeErrorResponse(Helper.DisassembleResponse(response));
                    Error error = new Error();
                    error.updateMessage(errRes.message);
                    error.Show();
                    Close();
                }

            }
        }

        private void CreateRoom(object sender, RoutedEventArgs e)
        {
            NewRoom newRoom = new NewRoom();
            Close();
            newRoom.Show();
        }

        private void JoinRoom(object sender, RoutedEventArgs e)
        {
            JoinRoom join = new JoinRoom();
            Close();
            join.Show();
        }

        private void Statistics(object sender, RoutedEventArgs e)
        {
            GetStatisticsResponse stats = GetAllStatistics();
            if (stats != null)
            {
                Statistics personalStats = new Statistics();
                personalStats.showStatistics(stats, username);
            }
        }

        private void Leaderboard(object sender, RoutedEventArgs e)
        {
            GetStatisticsResponse stats = GetAllStatistics();
            if (stats != null)
            {
                Statistics personalStats = new Statistics();
                personalStats.showStatistics(stats, "ALL");
            }
        }

        private void Highscores(object sender, RoutedEventArgs e)
        {
            GetStatisticsResponse stats = GetAllStatistics();
            if (stats != null)
            {
                Statistics personalStats = new Statistics();
                personalStats.showStatistics(stats, "LEADERS");
            }
        }

        private GetStatisticsResponse GetAllStatistics()
        {
            //Build and send message
            byte[] request = Serializer.SerializeStatsRequest();
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
                Close();
            }
            else if ((int)serializedResponse[0] == (int)CODES.STATS)
            {
                return Deserializer.DeserializeStatisticsResponse(result);
            }

            return null;

        }


    }
}
