#include "webserver.h"

WebServer::WebServer(ComunicationCenter *comunication)
{
  this->comunication = comunication;
}


void WebServer::run(){
    MainSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(MainSocket == -1){
        cout << "Error al crear el descriptor del socket" << endl;
        return;
    }

    int yes=1;
        if (setsockopt(MainSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
            cout << "Error al sobre escribir la configuracion del socket" << endl;
        }



    ServerInfo.sin_addr.s_addr = INADDR_ANY;
    ServerInfo.sin_family = AF_INET;
    ServerInfo.sin_port = htons(4495);
    memset(&ServerInfo.sin_zero,0,sizeof(ServerInfo.sin_zero));

    if(bind(MainSocket,(sockaddr *)&ServerInfo,(socklen_t)sizeof(ServerInfo)) < 0){
        cout << "Ya existe un socket atendiendo ese puerto " << endl;
        return;
    }

    listen(MainSocket,50);

    while(1){
        cout << "Esperando clientes "<< endl;
        sockaddr_in clientInfo;
        int socketID;
        socklen_t tam;
        socketID = accept(MainSocket,(sockaddr*)&clientInfo,&tam);

        if(socketID > 0){
            cout << "Nuevo cliente aceptado "<< endl;
            thread s(WebServer::CreateNewClient,socketID,this);
            s.detach();
        }else{
            cout << "Error al aceptar cliente"<< endl;
        }
    }


}


void WebServer::CreateNewClient(int idSocket, WebServer *parent){
   ClientHandler *o = new ClientHandler(parent->comunication);
   o->setSocketID(idSocket);
   parent->comunication->RegisterClient(o);
   o->start();
   delete o;
}
