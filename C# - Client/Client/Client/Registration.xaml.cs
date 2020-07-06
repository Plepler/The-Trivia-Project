﻿using System;
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
using System.Windows.Shapes;
using System.Data;
using System.Data.SqlClient;
using System.Text.RegularExpressions;

namespace Client
{
    /// <summary>  
    /// Interaction logic for Registration.xaml  
    /// </summary>  
    public partial class Registration : Window
    {
        public Registration()
        {
            InitializeComponent();
            new Communicator();//Start connection
        }
        private void Login_Click(object sender, RoutedEventArgs e)
        {
            Login login = new Login();
            login.Show();
            Close();
        }
        private void button2_Click(object sender, RoutedEventArgs e)
        {
            Reset();
        }
        public void Reset()
        {
            textBoxUsername.Text = "";
            textBoxEmail.Text = "";
            passwordBox1.Password = "";
            passwordBoxConfirm.Password = "";
        }
        private void WelcomeBack_Click(object sender, RoutedEventArgs e)
        {
            Welcome welcome = new Welcome();
            welcome.Show();
            Close();
        }
        private void Submit_Click(object sender, RoutedEventArgs e)
        {
            //Check if fields are valid
            if (textBoxEmail.Text.Length == 0)
            {
                errormessage.Text = "Enter an email.";
                textBoxEmail.Focus();
            }
            else if (!Regex.IsMatch(textBoxEmail.Text, @"^[a-zA-Z][\w\.-]*[a-zA-Z0-9]@[a-zA-Z0-9][\w\.-]*[a-zA-Z0-9]\.[a-zA-Z][a-zA-Z\.]*[a-zA-Z]$"))
            {
                errormessage.Text = "Enter a valid email.";
                textBoxEmail.Select(0, textBoxEmail.Text.Length);
                textBoxEmail.Focus();
            }
            else
            {
                string username = textBoxUsername.Text;
                string email = textBoxEmail.Text;
                string password = passwordBox1.Password;
                if (passwordBox1.Password.Length == 0)
                {
                    errormessage.Text = "Enter password.";
                    passwordBox1.Focus();
                }
                else if (passwordBoxConfirm.Password.Length == 0)
                {
                    errormessage.Text = "Enter Confirm password.";
                    passwordBoxConfirm.Focus();
                }
                else if (passwordBox1.Password != passwordBoxConfirm.Password)
                {
                    errormessage.Text = "Confirm password must be same as password.";
                    passwordBoxConfirm.Focus();
                }
                else
                {
                    errormessage.Text = "";

                    // build register message and send it
                    byte[] request = Serializer.SerializeRequest(new SignupRequest(username, password, email));
                    Communicator.SendMessage(request);
                    // recieve response and Deserialize it
                    byte[] serializedResponse = Communicator.recieveMessage();
                    byte[] result = Helper.DisassembleResponse(serializedResponse);

                    //Deserialize response according to CODE (first byte)
                    if ((int)serializedResponse[0] == (int)CODES.ERROR)
                    {
                        ErrorResponse errRes = Deserializer.DeserializeErrorResponse(result);
                        errormessage.Text = errRes.message;//Show error message
                    }
                    else if((int)serializedResponse[0] == (int)CODES.SIGNUP)
                    {
                        SignupResponse signupRes = Deserializer.DeserializeSignupResponse(result);
                        Menu menu = new Menu();
                        menu.SetUsername(username);
                        Close();
                        menu.Show();
                    }
                    else
                    {
                        errormessage.Text = "Unexpected error";
                    }
                    
                    Reset();
                }
            }
        }
    }
}