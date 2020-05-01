package main

/*
#cgo CXXFLAGS: -std=c++11
#cgo  CFLAGS: -I  /usr/local/include/
#cgo  CFLAGS: -I /usr/include/c++/8/
#cgo  CFLAGS: -I /usr/include/c++/8/x86_64-redhat-linux/
#cgo  CFLAGS: -I /usr/include/
#cgo  LDFLAGS: -L /usr/lib64/
#cgo  LDFLAGS: -L /usr/local/lib/ -lzmq -lstdc++

#include <zmq.h>
#include <string.h>
*/
import "C"

import (
    "fmt"
	"time"
	"unsafe"
)

func main() {
	endpoint := "tcp://localhost:5555"
	// generate a pull socket
	socket := unsafe.Pointer(C.zmq_socket(C.zmq_ctx_new(), C.ZMQ_REP))
	// bind to the socket
	rc1 := C.zmq_bind(socket, C.CString(endpoint))
	
	for {
	  // receive the message
	  buffer := [10]C.char{}
	  rc2 := C.zmq_recv(socket, unsafe.Pointer(&buffer), 10, 0)
  
	  //Do some 'work'
	  time.Sleep(time.Duration(1)*time.Second)
	  fmt.Println("Received Hello")
	  msg := C.CString("World")
	  rc3 := C.zmq_send(socket, unsafe.Pointer(&msg), 5, 0)
	  fmt.Printf("rc1 = %d, rc2 = %d, rc3 = %d\n", rc1, rc2, rc3)
	}
}
