#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <socketutil.h>
#include <iostream>
#include <comunicationcenter.h>
#include <QCryptographicHash>
#include <QString>
#include <QStringList>
#include <map>

#define MagicString "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"

class ComunicationCenter;

class ClientHandler
{
public:
    ClientHandler(ComunicationCenter *serviceCenter);
    void start();
    inline void setSocketID(int id){Fd_Socket = id;}
private:
    int Fd_Socket;
    ComunicationCenter * ServiceCenter;
    string Server_Handshake_Response(const string &Sec_WebSocket_Key);
    string GetKeyFromProtocolHeader(const string &ProtocolHeader);
    string httpRequestFromMap(const string &PeticionHead, SocketUtils::StringMap map);
};

#endif // CLIENTHANDLER_H
