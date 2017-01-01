#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <map>
#include <QString>
#include <websockettypemsn.h>
#include <iostream>
#include <vector>
using namespace std;

namespace SocketUtils {
   typedef enum TipoMensaje{
    //esto esta codificado en los 4 primeros bits del unsigned char que esta en la posicion [0] de lo que manda el websocket
    //Este protocolo esta definido en rfc6455 [https://tools.ietf.org/html/rfc6455#section-5.2]
    //Los  defini dentro del enum en hex xq ellos lo definieron asi pero creo q lo hacen por complicar las varas
    //xq perfectamente lo pueden poner en decimal
      WS_Continuation_Frame = 0x0,
      WS_Text_Frame = 0x1,
      WS_Binary_Frame = 0x2,
      WS_ConnectionClose = 0x8,
      WS_Ping = 0x9,
      WS_Pong = 0xA
   }TipoMensaje;
   typedef basic_string<unsigned char> BytesBuffer;
   typedef map<QString,QString> StringMap;
   void sendMsn(int fd , const QString &msn);
   QString ReadMSN(int fd);
   QString ReadMSNBytes(int fd);
   QString DecodeWebSocket(const BytesBuffer &rawString);
   int CalculoLongitudMensaje(const BytesBuffer & rawString);
   TipoMensaje DecodificarTipoMensaje(const unsigned char &firstByte);
}


#endif // SOCKETUTIL_H
