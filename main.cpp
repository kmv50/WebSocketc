#include <webserver.h>
#include <comunicationcenter.h>

WebServer *server;

int main(int argc, char *argv[])
{
  server = new WebServer(new ComunicationCenter);
  server->run();
  delete server;
}


/*
salida de programa

GET / HTTP/1.1
Host: 127.0.0.1:4495
Connection: Upgrade
Pragma: no-cache
Cache-Control: no-cache
Upgrade: websocket
Origin: file://
Sec-WebSocket-Version: 13
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.59 Safari/537.36
Accept-Encoding: gzip, deflate, sdch, br
Accept-Language: es-419,es;q=0.8,en;q=0.6
Sec-WebSocket-Key: 1UOtPb71u0LsL0UKffnA6A==
Sec-WebSocket-Extensions: permessage-deflate; client_max_window_bits


HTTP/1.1 101 Switching Protocols
Connection: Upgrade
Upgrade: websocket
Sec-WebSocket-Accept: U/RKXYaUGBQjnkm8W4yi+6+OSzw=

*/
