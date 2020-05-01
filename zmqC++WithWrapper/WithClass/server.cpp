//  Hello World server

#include "wrapperWithClass/socketWrapper.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
// 
using namespace std;

int main(int argc, char *argv[]) {
  // generate a pull socket
  ZMQSocket s(1);
  // bind to the socket
  s.bind("tcp://*:5555");
  
  while (1) {
    // receive the message
    string msg = s.receive();
    //Do some 'work'
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Received" << msg << endl;
    // send message
    cout << "Sending World" << "..." << endl;
    s.send("World");
  }

}
