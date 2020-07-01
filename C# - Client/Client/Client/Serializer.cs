using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// 
/// All Response classes
/// have necceseery members 
/// and basic constructors
/// 
/// In: Appropriate request
/// Out: byte buffer
/// 
/// </summary>


public class SignupRequest
{

    public string username;
    public string password;
    public string email;

    public SignupRequest(string username, string password, string email)
    {
        this.username = username;
        this.password = password;
        this.email = email;
    }
}
public class LoginRequest
{
    public string username;
    public string password;

    public LoginRequest(string username, string password)
    {
        this.username = username;
        this.password = password;
    }
}
public class GetPlayersInRoomRequest
{
    public uint roomId;

    public GetPlayersInRoomRequest(uint roomId)
    {
        this.roomId = roomId;
    }
}
public class JoinRoomRequest
{
    public uint roomId;

    public JoinRoomRequest(uint roomId)
    {
        this.roomId = roomId;
    }
}
public class CreateRoomRequest
{
    public string roomName;
    public uint maxUsers;
    public uint questionCount;
    public uint answerTimeout;

    public CreateRoomRequest(string roomName, uint maxUsers, uint questionCount, uint answerTimeout)
    {
        this.roomName = roomName;
        this.maxUsers = maxUsers;
        this.questionCount = questionCount;
        this.answerTimeout = answerTimeout;
    }
}



namespace Client
{
    public static class Serializer
    {
        public static byte[] SerializeResponse(SignupRequest request)
        {
            return Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
        }
        public static byte[] SerializeResponse(LoginRequest request)
        {
            return Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
        }
        public static byte[] SerializeResponse(GetPlayersInRoomRequest request)
        {
            return Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
        }
        public static byte[] SerializeResponse(JoinRoomRequest request)
        {
            return Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
        }
        public static byte[] SerializeResponse(CreateRoomRequest request)
        {
            return Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
        }
    }
}
