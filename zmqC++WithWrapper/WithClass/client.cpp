//  Hello World client

#include "wrapperWithClass/socketWrapper.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  // generate a pull socket
  ZMQSocket s(0);
  // open the connection
  cout << "Connecting to hello world server…" << endl;
  s.bind("tcp://localhost:5555");

  int request_nbr;
  for (request_nbr = 0; request_nbr != 10; request_nbr++) {
    // send a message
    cout << "Sending Hello " << request_nbr << "..." << endl;
    s.send("Hello");
    string msg = s.receive();
    cout << "Received " << msg << " " << request_nbr << endl;
  }
}
