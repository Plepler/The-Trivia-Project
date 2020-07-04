using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Data;
using System.Data.SqlClient;
using System.Text.RegularExpressions;
namespace Client
{
    /// <summary>  
    /// Interaction logic for MainWindow.xaml  
    /// </summary>   
    public partial class Login : Window
    {
        public Login()
        {
            InitializeComponent();
        }
        public Registration registration = new Registration();
        public Welcome welcome = new Welcome();
        private void button1_Click(object sender, RoutedEventArgs e)
        {
            

            if (textBoxUsername.Text.Length == 0)
            {
                errormessage.Text = "Enter an username.";
                textBoxUsername.Focus();
            }
            else
            {
                string username = textBoxUsername.Text;
                string password = passwordBox1.Password;

                // build register message and send it
                byte[] request = Serializer.SerializeRequest(new LoginRequest(username, password));
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
                else if ((int)serializedResponse[0] == (int)CODES.LOGIN)
                {
                    SignupResponse signupRes = Deserializer.DeserializeSignupResponse(result);

                    Menu menu = new Menu();
                    menu.Show();
                    Close();
                }

            }
        }
        private void buttonRegister_Click(object sender, RoutedEventArgs e)
        {
            registration.Show();
            Close();
        }

        private void WelcomeBack(object sender, RoutedEventArgs e)
        {
            Welcome welcome = new Welcome();
            welcome.Show();
            Close();
        }
    }
}