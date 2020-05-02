#ifndef __SOCKETWRAPPER_H__
#define __SOCKETWRAPPER_H__

#include <zmqpp/zmqpp.hpp>
#include <string>

using namespace std;
using namespace zmqpp;

// #ifdef __cplusplus
// extern "C" {
// #endif

class ZMQSocket {
    public:
        context my_context;
        socket_type my_type;
        socket my_socket;
        ZMQSocket();
        ~ZMQSocket();
        ZMQSocket(int type);
        void bind(string endpoint);
        void send(string s);
        string receive();
};

// #ifdef __cplusplus
// }
// #endif

#endif