using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


public class RoomData
{

    public uint id;
    public string name;
    public uint maxPlayers;
    public uint timePerQuestion;
    public uint isActive;
    public uint numOfQuestions;

    public RoomData(uint id, string name, uint maxPlayers, uint timePerQuestion, uint isActive, uint numOfQuestions)
    {
        this.id = id;
        this.name = name;
        this.maxPlayers = maxPlayers;
        this.timePerQuestion = timePerQuestion;
        this.isActive = isActive;
        this.numOfQuestions = numOfQuestions;
    }
}
public class ErrorResponse
{
	public string data;

    public ErrorResponse(string data)
    {
        this.data = data;
    }
}
//Login responses
public class LoginResponse
{
	public uint status;

    public LoginResponse(uint status)
    {
        this.status = status;
    }
}
public class SignupResponse
{
	public uint status;

    public SignupResponse(uint status)
    {
        this.status = status;
    }
}
public class LogoutResponse
{
	public uint status;

    public LogoutResponse(uint status)
    {
        this.status = status;
    }
}
//Room responses
public class GetRoomsResponse
{
	public uint status;
	public Queue<RoomData> rooms;

    public GetRoomsResponse(uint status, Queue<RoomData> rooms)
    {
        this.status = status;
        this.rooms = rooms;
    }
}
public class GetPlayersInRoomResponse
{
	public Queue<string> players;

    public GetPlayersInRoomResponse(Queue<string> players)
    {
        this.players = players;
    }
}
public class GetStatisticsResponse
{
	public uint status;
	public Queue<string> statistics;

    public GetStatisticsResponse(uint status, Queue<string> statistics)
    {
        this.status = status;
        this.statistics = statistics;
    }
}
public class JoinRoomResponse
{
	public uint status;

    public JoinRoomResponse(uint status)
    {
        this.status = status;
    }
}
public class CreateRoomResponse
{
	public uint status;

    public CreateRoomResponse(uint status)
    {
        this.status = status;
    }
}


namespace Client
{
    class Deserializer
    {
        //Deserialize, Deserialize, Deserialize.....
        //From byte array to json...
        //and from json to a response class...
        public ErrorResponse DeserializeErrorResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<ErrorResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
		public LoginResponse DeserializeLoginResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<LoginResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
		public SignupResponse DeserializeSignupResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<SignupResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
		public LogoutResponse DeserializeLogoutResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<LogoutResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
		public GetRoomsResponse DeserializeGetRoomResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<GetRoomsResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
		public GetPlayersInRoomResponse DeserializeGetPlayersResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<GetPlayersInRoomResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
		public GetStatisticsResponse DeserializeResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<GetStatisticsResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
		public JoinRoomResponse DeserializeJoinRoomResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<JoinRoomResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
		public CreateRoomResponse DeserializeCreateRoomResponse(byte[] buffer)
		{
            return JsonConvert.DeserializeObject<CreateRoomResponse>(Encoding.UTF8.GetString(buffer, 0, buffer.Length));
        }
    }
}
