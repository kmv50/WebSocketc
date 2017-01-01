#ifndef WEBSOCKETTYPEMSN_H
#define WEBSOCKETTYPEMSN_H
namespace SocketUtils {
typedef enum TipoMensaje{
 //esto esta codificado en los 4 primeros bits del unsigned char que esta en la posicion [0] de lo que manda el websocket
 //Este protocolo esta definido en rfc6455 [https://tools.ietf.org/html/rfc6455#section-5.2]
 //Los  defini dentro del enum en hex xq ellos lo definieron asi pero creo q lo hacen por complicar las varas
 //xq perfectamente lo pueden poner en decimal
   WS_Continuation_Frame = 0x0,
   WS_Text_Frame = 0x1,
   WS_Binary_Frame = 0x2,
   WS_ConnectionClose = 0x8,
   WS_Ping = 0x9,
   WS_Pong = 0xA
}TipoMensaje;
}
#endif // WEBSOCKETTYPEMSN_H
