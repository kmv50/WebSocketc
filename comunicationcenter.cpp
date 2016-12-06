#include "comunicationcenter.h"

ComunicationCenter::ComunicationCenter()
{

}

ComunicationCenter::~ComunicationCenter(){
    for(unsigned int i = 0 ; i < clientList.size() ; i++){
        delete (ClientHandler*)clientList[i];
    }
}

void ComunicationCenter::RegisterClient(ClientHandler *client){

    m_lock.lock();
        clientList.push_back(client);
    m_lock.unlock();

    cout << "Cliente registrado" << endl;
}


void ComunicationCenter::RemoverClient(ClientHandler *client){

}
