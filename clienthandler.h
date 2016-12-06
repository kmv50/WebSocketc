#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <socketutil.h>
#include <iostream>
#include <comunicationcenter.h>
#include <QCryptographicHash>
#include <QString>
#include <QStringList>
#include <map>

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
    QString Server_Handshake_Response(const QString &Sec_WebSocket_Key);
    QString GetKeyFromProtocolHeader(const QString &ProtocolHeader);
    QString httpRequestFromMap(const QString &PeticionHead, SocketUtils::StringMap map);
    QString AccessRequest(const QString &msn);
    void StarListen();
};

#endif // CLIENTHANDLER_H
