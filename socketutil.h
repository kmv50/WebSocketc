#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <map>
#include <QString>
using namespace std;

namespace SocketUtils {
   typedef map<QString,QString> StringMap;
   void sendMsn(int fd , const QString &msn);
   QString ReadMSN(int fd);
   QString DecodeWebSocket(const QString &msn);
}


#endif // SOCKETUTIL_H
