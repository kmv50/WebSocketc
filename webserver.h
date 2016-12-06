#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <clienthandler.h>
#include <string.h>

class WebServer
{
public:
    WebServer(ComunicationCenter * comunication);
    void run();
private:
    ComunicationCenter *comunication;
    sockaddr_in ServerInfo;
    int MainSocket;
    static void CreateNewClient(int idSocket,WebServer *parent);
};

#endif // WEBSERVER_H
