//  Hello World client

#include "wrapperWithoutClass/socketWrapper.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
  // generate a pull socket
  initSocket(0);
  // open the connection
  cout << "Connecting to hello world server…" << endl;
  bind("tcp://localhost:5555");

  int request_nbr;
  for (request_nbr = 0; request_nbr != 10; request_nbr++) {
    // send a message
    cout << "Sending Hello " << request_nbr << "..." << endl;
    send("Hello"); 
    string msg=receiveMsg();
    cout << "Received " << msg << " " << request_nbr << endl;
  }
}
