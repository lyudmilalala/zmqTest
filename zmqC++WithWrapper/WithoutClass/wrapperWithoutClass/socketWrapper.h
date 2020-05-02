#ifndef __SOCKETWRAPPER_H__
#define __SOCKETWRAPPER_H__

#include <zmqpp/zmqpp.hpp>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
using namespace zmqpp;

// #ifdef __cplusplus
// extern "C" {
// #endif

extern socket my_socket;
void initSocket(int type);
void bind(string endpoint);
void send(string s);
string receive();

// #ifdef __cplusplus
// }
// #endif

#endif