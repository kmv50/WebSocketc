#include "socketutil.h"

void SocketUtils::sendMsn(int fd , const QString  &msn){
    int bytesRead = send(fd,msn.toStdString().c_str(),msn.size(),0);
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

unsigned long int SocketUtils::CalculoLongitudMensaje(const BytesBuffer &rawString , int * bytesUsados){
    unsigned int  longitud = ((int)rawString[1]&127) ;
    /*
        Por ejemplo si el resultado de (unsigned int)rawString[1] es 158 en binario seria 111111110011110
        Pero como solo me interez el primer byte hago la operacion de [and] en binario osea      01111111 == 127
        Eso en decimal es 30                                                                     00011110 == 30
    */
    *bytesUsados += 1;
    if(longitud <= 125){ //como 30 es menor a 125 esta expresando la longitud del mensaje
        return longitud;
    }else if(longitud  == 126){
        //cuando el rawString[1] osea el segundo byte es 126 indica q la longitud del mensaje se expresa en los
        //dos siguientes bytes

        //para explicar esto voy a suponer de que del cliente se estan enviando 266 chars
        //entonces los valores para MSN_bytes_Size serian algo como esto:
        unsigned int MSN_bytes_Size[2] = {
            (unsigned int)rawString[2], //eje 1 en binario  00000001
            (unsigned int)rawString[3]  //eje 10 en binario 00001010
        };

        unsigned long longitudMSN = 0;

        // ahora en este punto se realiza la operacion de desplazamiento de bytes
        longitudMSN = (unsigned int)MSN_bytes_Size[0]<< 8;
        //(1  << 8)  00000001 << 8 = 100000000 que en decimal se expresa como 256
        longitudMSN = (unsigned int)MSN_bytes_Size[1]<< 0;
        //(10  << 8) 00001010 << 0 = 000001010 que en decimal se expresa como 10

        //osea 100000000 + 000001010 = 100001010 (266)
        *bytesUsados += 2;
        return longitudMSN;

     }else if(127){
        //Si (unsigned int)rawString[1] fuera igual a 127 se tendria que realizar este calculo

        unsigned int MSN_bytes_Size[8] = {
            (unsigned int)rawString[2],
            (unsigned int)rawString[3],
            (unsigned int)rawString[4],
            (unsigned int)rawString[5],
            (unsigned int)rawString[6],
            (unsigned int)rawString[7],
            (unsigned int)rawString[8],
            (unsigned int)rawString[9]
        };

        unsigned long int longitudMSN  = 0;//64 bits
        //Aqui como se puede ver q se hace algo igual a lo de arriba
        //la diferencia esq aqui se puede apreciar mas como funciona el desplazamiento de bytes
        // si se fija va corriendo a un ritmo de 8 bits
        longitudMSN += (unsigned long int )MSN_bytes_Size[0]<< 56;//64 bits
        longitudMSN += (unsigned long int )MSN_bytes_Size[1]<< 48;//64 bits
        longitudMSN += (unsigned long int )MSN_bytes_Size[2]<< 40;//64 bits
        longitudMSN += (unsigned long int )MSN_bytes_Size[3]<< 32;//64 bits
        longitudMSN += (unsigned int)      MSN_bytes_Size[4]<< 24;//32 bits
        longitudMSN += (unsigned int)      MSN_bytes_Size[5]<< 16;//32 bits
        longitudMSN += (unsigned short int)MSN_bytes_Size[6]<< 8;//16 bits
        longitudMSN += (unsigned short int)MSN_bytes_Size[7]<< 0;//16 bits
        *bytesUsados += 8;
        return longitudMSN;
     }




    return -1;//error los valores tiene que se menores o iguales a 127
}

SocketUtils::TipoMensaje  SocketUtils::DecodificarTipoMensaje(const unsigned char &firstByte){
   //ahora esta funcion lo que hace es retornar que tipo de datos trae el mensaje
   // pueden ser los que estan definidos en enum TipoMensaje
   // ahora el tipo de mensaje viene codificado en los 4 primeros bits del primer byte
   // Para sacarle esos 4 bits al unsigned char  hay que hacer una operacion de and [&] //no es la lambad
   int type = (((unsigned int)firstByte) & 15);
   //Ahora por las pruebas que e echo casi siempre es un mensaje de tipo text y lo que llega en [firstByte]
   // es 129 osea 10000001
   // [&] 15 osea 00001111
   //             00000001 ==  1  osea = TipoMensaje.WS_Text_Frame osea 0x1

   return (TipoMensaje)type; // esto es un salto de fe ya q confio q el resultado de la operacion anterior
   //concuerde con algun tipo del enum
   //lo correcto seria hacer un poco de if pero que pereza
}

QString SocketUtils::DecodeWebSocket(BytesBuffer rawString){
   /* for(int i = 0 ; i < rawString.size() ; i++){
        cout << (unsigned int)rawString[i] << " ";
    }*/
    cout << endl;
    TipoMensaje tipo = DecodificarTipoMensaje(rawString[0]);
    int bytesUsados = 1;//el 1 es por el byte usado arriba siempre es 1 solo byte
    unsigned long int longitud = CalculoLongitudMensaje(rawString,&bytesUsados);

    if((int)longitud == -1){
        cout << "Error obtenido la longitud del mensaje "<<endl;
        return NULL;
    }

    //  cout << "tipo de mensaje " << tipo << " longitud "<< longitud << " bytes usados " <<  bytesUsados << endl;

    //el tamano del array esta definido por el protocolo indica 4
    unsigned int key[4] = {
        (unsigned int)rawString[bytesUsados++],
        (unsigned int)rawString[bytesUsados++],
        (unsigned int)rawString[bytesUsados++],
        (unsigned int)rawString[bytesUsados++],
    };
    // cout  <<"key "<<bytesUsados << endl;
    QString mensaje;
    //i empieza en contando los bites ya usados
    //pero el problema esq eso me afectaria al hacer el ciclo ya que la longitud si se cuenta desde 0
    //entonces por eso ese desmadre en el for
    for (unsigned int i = bytesUsados; (i-bytesUsados+1) <= longitud; i++) {
        mensaje += (rawString[i] ^ key[(i-bytesUsados) % 4]);
    }
    /*
        0  %  4 = 0
        1  %  4 = 1
        2  %  4 = 2
        3  %  4 = 3
        ...
        7  %  4 = 3
        8  %  4 = 0
    */
    return mensaje;
}


/*
129 164 232 243 223 247 147 209 146 132 134 209 229 213 137 155 176 133 137 211 172 158 200 128 182 133 158 150 255 146 155 135 190 215 133 154 186 133 140 146 253 138
tipo de mensaje 1 longitud 36 bytes usados 2
key 6
{"Msn":"ahora si sirve esta mierda"}
*/
