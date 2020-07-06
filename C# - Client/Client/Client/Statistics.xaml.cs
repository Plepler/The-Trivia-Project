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
    /// Interaction logic for Statistics.xaml
    /// </summary>
    public partial class Statistics : Window
    {
        public Statistics()
        {
            InitializeComponent();
        }

        /// <summary> Show statistics of username
        /// username = <name>: personal
        /// username = ALL: all users
        /// username = LEADERS: Top 3
        /// </summary>
        /// <param name="flag"> flag tells us whos statistics to show </param>
        public void showStatistics(GetStatisticsResponse response, string username)
        {
            statistcis_list.Items.Clear();
            if (username == "ALL")
            {
                while (response.statistics.Count() != 0)//Iterate over all rooms
                {
                    string player = response.statistics.Dequeue() + "\nAvergage time: " + response.statistics.Dequeue() + "\nCorrect answers: " + response.statistics.Dequeue() + "\nTotal answers: " + response.statistics.Dequeue() + "\nTotal games: " + response.statistics.Dequeue() + "\n";
                    statistcis_list.Items.Add(player);
                }
            }
            else if (username == "LEADERS")
            {
                for (int i = 0; i < 3 && response.statistics.Count() != 0; i++)
                {
                    string player = response.statistics.Dequeue() + "\nAvergage time: " + response.statistics.Dequeue() + "\nCorrect answers: " + response.statistics.Dequeue() + "\nTotal answers: " + response.statistics.Dequeue() + "\nTotal games: " + response.statistics.Dequeue() + "\n";
                    statistcis_list.Items.Add(player);
                }

            }
            else
            {
                Queue<string> relevent_player = new Queue<string>(response.statistics);
                foreach (string i in response.statistics)//Iterate over all rooms
                {
                    if (i == username)
                    {
                        string player = relevent_player.Dequeue() + "\nAvergage time: " + relevent_player.Dequeue() + "\nCorrect answers: " + relevent_player.Dequeue() + "\nTotal answers: " + relevent_player.Dequeue() + "\nTotal games: " + relevent_player.Dequeue() + "\n";
                        statistcis_list.Items.Add(player);
                        break;
                    }
                    else
                    {
                        relevent_player.Dequeue();
                    }

                }
            }



            Show();
        }

        private void CloseWindow(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }


    }
