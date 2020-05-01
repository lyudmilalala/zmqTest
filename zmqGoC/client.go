package main

/*
#cgo CXXFLAGS: -std=c++11
#cgo  CFLAGS: -I  /usr/local/include/
#cgo  CFLAGS: -I  /usr/local/include/c++/9.3.0/
#cgo  CFLAGS: -I  /usr/local/include/c++/9.3.0/x86_64-apple-darwin18/
#cgo  LDFLAGS: -L /usr/local/lib/ -lzmq -lstdc++
#include <zmq.h>
#include <string.h>
*/
import "C"

import (
    "fmt"
	"unsafe"
)

func main() {
	endpoint := "tcp://localhost:5555"
	// open the connection
	fmt.Println("Connecting to hello world server…")

	// generate a pull socket
	socket := unsafe.Pointer(C.zmq_socket(C.zmq_ctx_new(), C.ZMQ_REQ))
	// bind to the socket
	rc1 := C.zmq_bind(socket, C.CString(endpoint))
	
	for request_nbr := 0; request_nbr != 10; request_nbr++ {
		fmt.Printf("Sending Hello %d...\n",request_nbr)
		msg := C.CString("Hello")
		rc2 := C.zmq_send(socket, unsafe.Pointer(&msg), 5, 0)
		buffer := [10]C.char{}
		rc3 := C.zmq_recv(socket, unsafe.Pointer(&buffer), 10, 0)
		fmt.Printf("Receive World %d\n",request_nbr)
		fmt.Printf("rc1 = %d, rc2 = %d, rc3 = %d\n", rc1, rc2, rc3)
	}
	C.zmq_close(socket)
}
