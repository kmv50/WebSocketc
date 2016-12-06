#ifndef COMUNICATIONCENTER_H
#define COMUNICATIONCENTER_H
#include <clienthandler.h>
#include <vector>
#include <thread>
#include <mutex>


class ClientHandler;


class ComunicationCenter
{
public:
    ComunicationCenter();
    ~ComunicationCenter();
    void RegisterClient(ClientHandler *client);
    void RemoverClient(ClientHandler *client);
    void SendBroadCast(const string &msn);
private:
    std::vector<ClientHandler *> clientList;
    mutex m_lock;
};

#endif // COMUNICATIONCENTER_H
