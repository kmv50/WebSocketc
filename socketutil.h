#ifndef SOCKETUTIL_H
#define SOCKETUTIL_H
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <map>
using namespace std;

namespace SocketUtils {
   typedef map<string,string> StringMap;
   void sendMsn(int fd , const string  &msn);
   string ReadMSN(int fd);
}


#endif // SOCKETUTIL_H
