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
        public Menu()
        {
            InitializeComponent();
        }

        private void CreateRoom(object sender, RoutedEventArgs e)
        {
            NewRoom newRoom = new NewRoom();
            Close();
            newRoom.Show();
        }

        private void JoinRoom(object sender, RoutedEventArgs e)
        {

        }

        private void Statistics(object sender, RoutedEventArgs e)
        {

        }

        private void CloseProgram(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
