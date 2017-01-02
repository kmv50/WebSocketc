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
#include <ostream>
using namespace std;

namespace SocketUtils {
   typedef basic_string<unsigned char> BytesBuffer;
   typedef map<QString,QString> StringMap;
   void sendMsn(int fd , const QString &msn);
   QString ReadMSN(int fd);
   QString ReadMSNBytes(int fd);
   QString DecodeWebSocket(BytesBuffer rawString);
   unsigned long CalculoLongitudMensaje(const BytesBuffer &rawString, int *bytesUsados);
   TipoMensaje DecodificarTipoMensaje(const unsigned char &firstByte);
   void sendMsnEncode(const int fd , const QString &msnStr);
}


#endif // SOCKETUTIL_H
