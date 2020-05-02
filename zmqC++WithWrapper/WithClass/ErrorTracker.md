Error Tracker
======================================
## Description ##
This is an implementation of ZMQ messager in **C++** with `zmqpp` library.

This case is written to test whether a `zmqpp` function wrapper can work properly in a C++ program, as they have the same language.

The wrapper `.cpp` contains a class `ZMQSocket` with:
* A zmqpp::context
* A zmqpp::socket_type
* A zmqpp::socket
* A initialization function for the socket
* A binding function to bind the socket with an endpoint
* A sending function
* A receiving function

## Compile and Running Status ##
Can be successfully compiled. But the client would fail to start running.
```
# g++ -g wrapperWithClass/socketWrapper.cpp client.cpp -o client -std=c++11 -lzmq /usr/local/lib/libzmqpp.a
# ./client 
Connecting to hello world server…
terminate called after throwing an instance of 'zmqpp::zmq_internal_exception'
  what():  No such device
Aborted
```
I think the problem is caused by the `zmqpp::socket` we stored in the class. 

We need to construct all variables in a class before constructing the class itself, otherwise, error such as below will occurs:
```
wrapperWithClass/socketWrapper.cpp:3:12: error: constructor for 'ZMQSocket' must
      explicitly initialize the member 'my_socket' which does not have a default
      constructor
ZMQSocket::ZMQSocket(int type) {
```
In normal cases, we will solve the problem with a structure as:
```
ZMQSocket::ZMQSocket(int type) : my_socket(my_context, my_type) {
```
But here, our socket type need to be determined by the input, so we first give `my_socket` a default `my_type` value, and then modified it in the constructor by code as:
```
ZMQSocket::ZMQSocket(int type) : my_socket(my_context, socket_type::reply) {
    if (type == 0) {
		my_type = socket_type::req;
	} else {
		my_type = socket_type::reply;
	}
    my_socket=socket(my_context, my_type);
}
```
After such modification, the server can start running properly, but the client will abort as above.

**Have not figured out how to fix yet.**

### Environment Configuration ###
Operating System
```
# cat /etc/redhat-release
CentOS Linux release 8.1.1911 (Core) 
```

gcc/g++ version
```
# g++ -v
Using built-in specs.
COLLECT_GCC=g++
COLLECT_LTO_WRAPPER=/usr/libexec/gcc/x86_64-redhat-linux/8/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-redhat-linux
Configured with: ../configure --enable-bootstrap --enable-languages=c,c++,fortran,lto --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-shared --enable-threads=posix --enable-checking=release --enable-multilib --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --with-gcc-major-version-only --with-linker-hash-style=gnu --enable-plugin --enable-initfini-array --with-isl --disable-libmpx --enable-offload-targets=nvptx-none --without-cuda-driver --enable-gnu-indirect-function --enable-cet --with-tune=generic --with-arch_32=x86-64 --build=x86_64-redhat-linux
Thread model: posix
gcc version 8.3.1 20190507 (Red Hat 8.3.1-4) (GCC) 
```
go environment
```
go env
GOARCH="amd64"
GOBIN=""
GOCACHE="/root/.cache/go-build"
GOEXE=""
GOFLAGS=""
GOHOSTARCH="amd64"
GOHOSTOS="linux"
GOOS="linux"
GOPATH="/root/go"
GOPROXY=""
GORACE=""
GOROOT="/usr/lib/golang"
GOTMPDIR=""
GOTOOLDIR="/usr/lib/golang/pkg/tool/linux_amd64"
GCCGO="gccgo"
CC="gcc"
CXX="g++"
CGO_ENABLED="1"
GOMOD=""
CGO_CFLAGS="-g -O2"
CGO_CPPFLAGS=""
CGO_CXXFLAGS="-std=c++11"
CGO_FFLAGS="-g -O2"
CGO_LDFLAGS="-g -O2"
PKG_CONFIG="pkg-config"
GOGCCFLAGS="-fPIC -m64 -pthread -fmessage-length=0 -fdebug-prefix-map=/tmp/go-build332265408=/tmp/go-build -gno-record-gcc-switches"
```
