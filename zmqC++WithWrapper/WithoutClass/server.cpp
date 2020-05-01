//  Hello World server

#include "wrapperWithoutClass/socketWrapper.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
// 
using namespace std;

int main(int argc, char *argv[]) {
  // generate a pull socket
  initSocket(1);
  // bind to the socket
  bind("tcp://*:5555");
  
  while (1) {
    // receive the message
    std::string msg=receiveMsg();
    //Do some 'work'
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Received" << msg << endl;
    // send message
    cout << "Sending World" << "..." << endl;
    send("World");
  }

}
