#include "socketutil.h"

void SocketUtils::sendMsn(int fd , const string  &msn){
    unsigned int bytesRead = send(fd,msn.c_str(),msn.size(),0);
    if(bytesRead < msn.size()){
        throw string("Error al enviar Mensaje");
    }
}

string SocketUtils::ReadMSN(int fd){

    char buffer[10] = {0};
    std::string databuffer;
    int bytesRead = 0;
    //bloquea hasta que le llegue algo
    bytesRead = recv(fd,buffer,10,0);
    if(bytesRead < 0){
        throw string("Cliente desconectado");
    }
    databuffer.append(buffer,bytesRead);

    //hace el read no bloqueante
    const int flags = fcntl (fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);

    while(1){
        bytesRead = recv(fd,buffer,10,0);
        if(bytesRead < 0){
            break;
        }
        databuffer.append(buffer,bytesRead);
    }

    fcntl(fd, F_SETFL, flags);
    //restaura la configurarion del read para este socket
    return databuffer;
}
