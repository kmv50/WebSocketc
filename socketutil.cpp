#include "socketutil.h"

void SocketUtils::sendMsn(int fd , const QString  &msn){
    unsigned int bytesRead = send(fd,msn.toStdString().c_str(),msn.size(),0);
    if(bytesRead < msn.size()){
        throw string("Error al enviar Mensaje");
    }
}

QString SocketUtils::ReadMSN(int fd){
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
    return QString::fromStdString(databuffer);
}


QString SocketUtils::ReadMSNBytes(int fd){
    unsigned char buffer[10] = {0};
    BytesBuffer databuffer;
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
        bytesRead = recv(fd,&buffer,10,0);
        if(bytesRead < 0){
            break;
        }

        databuffer.append(buffer,bytesRead);
    }

    fcntl(fd, F_SETFL, flags);
    //restaura la configurarion del read para este socket
    return DecodeWebSocket(databuffer);
}

int SocketUtils::CalculoLongitudMensaje(const BytesBuffer &rawString){
    int longitud;
    cout << (unsigned int)rawString[1] << " " << ((int)rawString[1]&127) << endl; ///01111111(127)
    longitud = ((int)rawString[1]&127) ;
    /*
        Por ejemplo si el resultado de (unsigned int)rawString[1] es 158 en binario seria 111111110011110
        Pero como solo me interez el primer byte hago la operacion de and en binario osea        01111111 == 127
        Eso en decimal es 30                                                                     00011110 == 30
        y como 30 es menor a 125 esta expresando la longitud del mensaje
    */

    if(longitud <= 125){
        return longitud;
    }else if(longitud  == 126){

    }else{

    }


    /*
        Si (unsigned int)rawString[1] fuera igual a 127 se tendria que realizar este calculo
    */

    return longitud;
}

SocketUtils::TipoMensaje  SocketUtils::DecodificarTipoMensaje(const unsigned char &firstByte){
    cout <<"Tipo Mensaje == " << (unsigned int)firstByte << endl;
   //ahora esta funcion lo que hace es retornar que tipo de datos trae el mensaje
   // pueden ser los que estan definidos en enum TipoMensaje
   // ahora este tipo de mensaje viene codificado en los 4 primeros bits del primer byte
   // Para sacarle esos 4 bits al unsigned char  hay que hacer una operacion de and [&] //no es la lambad
   int type = (((unsigned int)firstByte) & 15); // 15 en binario se expresa como 00001111
   return (TipoMensaje)type; // esto es un salto de fe ya q confio q el resultado de la operacion anterior
   //concuerde con algun tipo del enum
   //lo correcto seria hacer el poco de if pero que pereza

   //Ahora por las pruebas que e echo casi siempre es un mensaje de tipo text y lo que llega en [firstByte]
   // es 129 osea 10000001
   // [&] 15 osea 00001111
   //             00000001 ==  1  osea = TipoMensaje.WS_Text_Frame osea 0x1
}

QString SocketUtils::DecodeWebSocket(const BytesBuffer &rawString){
    //(129) 10000001 & (0x0f)100000011111  == 1  (rawString[0]&0x0f)
    cout << (unsigned int)rawString[0] << " "<< (rawString[0]&0x0f) << endl;
    TipoMensaje tipo = DecodificarTipoMensaje(rawString[0]);
    int longitud = CalculoLongitudMensaje(rawString);


    return "algo";
}
