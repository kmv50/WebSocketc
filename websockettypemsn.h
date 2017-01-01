#ifndef WEBSOCKETTYPEMSN_H
#define WEBSOCKETTYPEMSN_H
namespace SocketUtils {
typedef enum WebSocketMSNType{
   FrameIncomming = 0x0, //denotes a continuation frame
   FrameText = 0x1,// denotes a text frame
   FrameBinary = 0x2,// denotes a binary frame
   CloseSignal =  0x8, // denotes a connection close
   Ping = 0x9,// denotes a ping
   Pong = 0xA// denotes a pong
}WebSocketMSNType;
}
#endif // WEBSOCKETTYPEMSN_H
