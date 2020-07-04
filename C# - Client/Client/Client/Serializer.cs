using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
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

enum CODES { ERROR = 0, LOGIN = 100, SIGNUP, LOGOUT, OK = 200, GET_ROOM, GET_PLAYER, STATS, JOIN, CREATE };

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
        /// <summary> To all serialize functions
        /// This function get a request
        /// serialize it: from struct to json format
        /// and from json to byte array
        /// then add a appropriate code
        /// </summary>
        /// <param name="request"> The request that will be serialized </param>
        /// <returns> the serialized code + request in a byte array </returns>
        /// 

        public static byte[] SerializeRequest(SignupRequest request)
        {
            //Serialize
            byte[] serializedReq = Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
            int requestSize = serializedReq.Length;
            byte[] result = new byte[5 + requestSize];
            //Add code, length and serialized request
            result[0] = (int)CODES.SIGNUP;//Add code
            System.Buffer.BlockCopy(itob(requestSize), 0, result, 1, 4);//Copy serialized length
            System.Buffer.BlockCopy(serializedReq, 0, result, 5, requestSize);//Copy serialized code

            return result;
        }
        public static byte[] SerializeRequest(LoginRequest request)
        {
            //Serialize
            byte[] serializedReq = Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
            int requestSize = serializedReq.Length;
            byte[] result = new byte[5 + requestSize];
            //Add code, length and serialized request
            result[0] = (int)CODES.LOGIN;//Add code
            System.Buffer.BlockCopy(itob(requestSize), 0, result, 1, 4);//Copy serialized length
            System.Buffer.BlockCopy(serializedReq, 0, result, 5, requestSize);//Copy serialized code

            return result;
        }
        public static byte[] SerializeRequest(GetPlayersInRoomRequest request)
        {
            //Serialize
            byte[] serializedReq = Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
            int requestSize = serializedReq.Length;
            byte[] result = new byte[5 + requestSize];
            //Add code, length and serialized request
            result[0] = (int)CODES.GET_PLAYER;//Add code
            System.Buffer.BlockCopy(itob(requestSize), 0, result, 1, 4);//Copy serialized length
            System.Buffer.BlockCopy(serializedReq, 0, result, 5, requestSize);//Copy serialized code

            return result;
        }
        public static byte[] SerializeRequest(JoinRoomRequest request)
        {
            //Serialize
            byte[] serializedReq = Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
            int requestSize = serializedReq.Length;
            byte[] result = new byte[5 + requestSize];
            //Add code, length and serialized request
            result[0] = (int)CODES.JOIN;//Add code
            System.Buffer.BlockCopy(itob(requestSize), 0, result, 1, 4);//Copy serialized length
            System.Buffer.BlockCopy(serializedReq, 0, result, 5, requestSize);//Copy serialized code

            return result;
        }
        public static byte[] SerializeRequest(CreateRoomRequest request)
        {
            //Serialize
            byte[] serializedReq = Encoding.ASCII.GetBytes(JsonConvert.SerializeObject(request));
            int requestSize = serializedReq.Length;
            byte[] result = new byte[5 + requestSize];
            //Add code, length and serialized request
            result[0] = (int)CODES.CREATE;//Add code
            System.Buffer.BlockCopy(itob(requestSize), 0, result, 1, 4);//Copy serialized length
            System.Buffer.BlockCopy(serializedReq, 0, result, 5, requestSize);//Copy serialized code

            return result;
        }
        public static byte[] SerializeStatsRequest()
        {
            //Serialize
            int requestSize = 0;
            byte[] result = new byte[5];
            //Add code, length and serialized request
            result[0] = (int)CODES.STATS;//Add code
            System.Buffer.BlockCopy(itob(requestSize), 0, result, 1, 4);//Copy serialized length

            return result;
        }
        public static byte[] SerializeRoomsRequest()
        {
            //Serialize
            int requestSize = 0;
            byte[] result = new byte[5];
            //Add code, length and serialized request
            result[0] = (int)CODES.GET_ROOM;//Add code
            System.Buffer.BlockCopy(itob(requestSize), 0, result, 1, 4);//Copy serialized length

            return result;
        }

        //Int to 4 bytes
        public static byte[] itob(int n)
        {
            byte[] res = new byte[4];
            res[0] = (byte)(n >> 24);
            res[0] = (byte)(n >> 16);
            res[0] = (byte)(n >> 8);
            res[0] = (byte)(n);

            return res;
        }
    }
}
