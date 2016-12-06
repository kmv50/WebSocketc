#include "clienthandler.h"

ClientHandler::ClientHandler(ComunicationCenter *serviceCenter)
{
    ServiceCenter = serviceCenter;
}



void ClientHandler::start(){
 cout << "atendiendo al cliente "<< Fd_Socket << endl;
 cout << "Request de acceso"<< endl;
 string msn;
 try{
  msn = SocketUtils::ReadMSN(Fd_Socket);
 }catch(string ex){
     cout << ex << endl;
     ServiceCenter->RemoverClient(this);
 }

 cout << msn << endl;
 try{
   // SocketUtils::StringMap httpResponce;

   // httpResponce["Host"] = "127.0.0.1:4495";
   /* httpResponce["Upgrade"] = "websocket";
    httpResponce["Connection"] = "Upgrade";
    httpResponce["Sec-WebSocket-Accept"] = Server_Handshake_Response(GetKeyFromProtocolHeader(msn));
    //httpResponce["Sec-WebSocket-Version"] = "13";
    string responce = httpRequestFromMap("HTTP/1.1 101 Switching Protocols",httpResponce);
    cout <<  responce ;
    */
    QString key = QString::fromStdString(GetKeyFromProtocolHeader(msn)).trimmed();

    QString keyresuelta = key+"258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    keyresuelta = keyresuelta.trimmed();

       QCryptographicHash sha1(QCryptographicHash::Sha1);
       sha1.addData(keyresuelta.toUtf8());
       QString accpetKey = sha1.result().toBase64();
    QString responce = "HTTP/1.1 101 Switching Protocols\r\n";
    responce += "Connection: Upgrade\r\n";
    responce += "Upgrade: websocket\r\n";
    responce += "Sec-WebSocket-Accept: "+accpetKey+"\r\n";
    responce += "\r\n";
    cout << responce.toStdString();
    SocketUtils::sendMsn(Fd_Socket,responce.toStdString());

 }catch(string e){
     cout << e << endl;
 }

 // SocketUtils::sendMsn();
// while(1){

// }

 shutdown(Fd_Socket,SHUT_RDWR);
}

string ClientHandler::httpRequestFromMap(const string &PeticionHead , SocketUtils::StringMap map){
    string httpString = PeticionHead + "\r\n";
    for (auto& node : map) {
        httpString +=  node.first + ":"+node.second+"\r\n";
    }
    return httpString+"\r\n";
}

string ClientHandler::GetKeyFromProtocolHeader(const string &ProtocolHeader){
   QStringList lst = QString::fromStdString(ProtocolHeader).split("\r\n");
   foreach (QString value, lst) {
       QStringList row = value.split(":");
       if(row.size() > 0){
           if(row[0] == "Sec-WebSocket-Key"){
               return row[1].toStdString();
           }
       }
   }
   throw string("Http rquest invalido");

}

string ClientHandler::Server_Handshake_Response(const string &Sec_WebSocket_Key){
    QCryptographicHash sha1(QCryptographicHash::Sha1);
    string Handshake = Sec_WebSocket_Key+"258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    std::remove(Handshake.begin(), Handshake.end(), ' ');
    cout << Handshake << "END" << endl;
    sha1.addData(Handshake.c_str(),Handshake.size());
    return QString(sha1.result().toBase64()).toStdString();
}





/*
#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>

std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    throw std::invalid_argument("id");
}

int main()
{
    auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';

    double gpa1;
    char grade1;
    std::string name1;
    std::tie(gpa1, grade1, name1) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa1 << ", "
              << "grade: " << grade1 << ", "
              << "name: " << name1 << '\n';
}
*/
