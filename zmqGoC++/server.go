package main

/*
#cgo CXXFLAGS: -std=c++11
#cgo  CFLAGS: -I  /usr/local/include/
#cgo  CFLAGS: -I /usr/include/c++/8/       
#cgo  CFLAGS: -I /usr/include/c++/8/x86_64-redhat-linux/
#cgo  LDFLAGS: -L /usr/local/lib /usr/local/lib/libzmqpp.a -lzmq -lstdc++
#include "wrapperWithoutClass/socketWrapper.h"
#include <string>
*/
import "C"

import (
    "fmt"
    "time"
)

func main() {
	endpoint := "tcp://localhost:5555"
	// generate a pull socket
	C.initSocket(1)
	// bind to the socket
	C.bind(C.string(endpoint))
	for {
	  // receive the message
	  text := C.GoString(C.receive())
  
	  //Do some 'work'
	  time.Sleep(time.Duration(1)*time.Second)
	  fmt.Println("Received Hello")
	  C.send(C.CString("World"))
	}
}
