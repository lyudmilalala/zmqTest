package main

/*
#cgo CXXFLAGS: -std=c++11
#cgo  CFLAGS: -I /usr/local/include/
#cgo  CFLAGS: -I /usr/include/c++/8/
#cgo  CFLAGS: -I /usr/include/c++/8/x86_64-redhat-linux/
#cgo  CFLAGS: -I /usr/include/
#cgo  LDFLAGS: -L /usr/lib64/
#cgo  LDFLAGS: /usr/local/lib/libzmqpp.a -lzmq -lstdc++
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
	C.initSocket(0)

	// open the connection
	fmt.Println("Connecting to hello world server…")
	C.bind(C.CString(endpoint))
	for request_nbr := 0; request_nbr != 10; request_nbr++ {
		fmt.Printf("Sending Hello %d...\n",request_nbr)
		// send the message
		C.send(C.CString("Hello"))

	  	text := C.GoString(C.receive())
		fmt.Printf("Receive %s %d\n",text, request_nbr)
	}
}
