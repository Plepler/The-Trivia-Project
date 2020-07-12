using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Client
{
    public class Helper
    {
        public static Mutex communicatorMutex = new Mutex();
        /// <summary>
        /// 
        /// This function takes the serialized response from
        /// the server and disassembles it
        /// 
        /// </summary>
        /// <param name="serializedResponse"> The unprocessed response from the server </param>
        /// <returns> The response itself without length or code </returns>
        public static byte[] DisassembleResponse(byte[] serializedResponse)
        {
            byte[] result;
            int length = 0;
            byte[] serializedLength = new byte[4];

            // Get length and deserialize it
            System.Buffer.BlockCopy(serializedResponse, 1, serializedLength, 0, 4);// Get serialized length
            length = Deserializer.btoi(serializedLength);// Deserialize length
            if (length > 0)
            {
                // Get response itself
                result = new byte[length];
                System.Buffer.BlockCopy(serializedResponse, 5, result, 0, length);
                return result;
            }
            return null;
        }

        public static GetRoomsResponse GetRooms()
        {
            byte[] request = Serializer.SerializeRoomsRequest();
            Communicator.SendMessage(request);

            //Recieve message
            byte[] serializedResponse = Communicator.recieveMessage();
            byte[] result = Helper.DisassembleResponse(serializedResponse);

            if ((int)serializedResponse[0] == (int)CODES.ERROR)
            {
                ErrorResponse errRes = Deserializer.DeserializeErrorResponse(result);
                Error error = new Error();
                error.updateMessage(errRes.message);
                error.Show();
                return null;
            }
            else
            {
                return Deserializer.DeserializeGetRoomResponse(result);
            }
        }
    }
}
