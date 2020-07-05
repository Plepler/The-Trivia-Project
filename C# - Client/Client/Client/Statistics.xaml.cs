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

        /// <summary>
        /// username = <name>: personal
        /// username = ALL: all users
        /// username = LEADERS: Top 3
        /// </summary>
        /// <param name="flag"></param>
        public void showStatistics(GetStatisticsResponse response, string username)
        {
            if (username == "ALL")
            {
                while (response.statistics.Count() != 0)//Iterate over all rooms
                {
                    statsBlock.Text = response.statistics.Dequeue() + "\nAvergage time: " + response.statistics.Dequeue() + "\nCorrect answers: " + response.statistics.Dequeue() + "\nTotal answers: " + response.statistics.Dequeue() + "\nTotal games: " + response.statistics.Dequeue();
                }
            }
            else if (username == "LEADERS")
            {
                for (int i = 0; i < 3 && response.statistics.Count() != 0; i ++)
                {
                    statsBlock.Text = response.statistics.Dequeue() + "\nAvergage time: " + response.statistics.Dequeue() + "\nCorrect answers: " + response.statistics.Dequeue() + "\nTotal answers: " + response.statistics.Dequeue() + "\nTotal games: " + response.statistics.Dequeue();
                }
            }
            else
            {
                foreach (string i in response.statistics)//Iterate over all rooms
                {
                    if (i == username)
                    {
                        statsBlock.Text = response.statistics.Dequeue() + "\nAvergage time: " + response.statistics.Dequeue() + "\nCorrect answers: " + response.statistics.Dequeue() + "\nTotal answers: " + response.statistics.Dequeue() + "\nTotal games: " + response.statistics.Dequeue();
                        break;
                    }
                    else
                    {
                        response.statistics.Dequeue();
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
