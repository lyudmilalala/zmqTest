Error Tracker
======================================
## Description ##
This is an implementation of ZMQ messager in **Golang** with `cgo` and `zmqpp` C++ library.

To export the C++ functions as C functions, I add a wrapper class with `extern C` to the project. The Go functions call `C.function` to use the `zmqpp` library.

The wrapper `.cpp` contains:
* A zmqpp::socket
* A initialization function for the socket
* A binding function to bind the socket with an endpoint
* A sending function
* A receiving function

## Compile and Running Status ##
Error for compiling: ask for `std=c++11` even if the configuration is already set to `std=c++11`
```
# go build client.go 
# command-line-arguments
In file included from /usr/include/c++/8/unordered_map:35,
                 from /usr/local/include/zmqpp/message.hpp:23,
                 from /usr/local/include/zmqpp/zmqpp.hpp:64,
                 from ./wrapperWithoutClass/socketWrapper.h:4,
                 from ./client.go:11:
/usr/include/c++/8/bits/c++0x_warning.h:32:2: error: #error This file requires compiler and library support for the ISO C++ 2011 standard. This support must be enabled with the -std=c++11 or -std=gnu++11 compiler options.
 #error This file requires compiler and library support \
  ^~~~~
```
The C++ wrapper functions were originally written in the **header** of the Golang class. After the compiler gave this error, I moved them to an individual wrapper class. But the error was still there.

I added `-std=c++11` in not only `CGO_CXXFLAGS`, but also `CXXFLAGS` in the Go header. I also added `=lstdc++` in the `LDFLAGS` header. But they all did't work.

I have read that variables in `extern C` needs to follow rules of **C** instead of rules of **C++**. Indeed I guess the type `string` returned by the `receive()` method may cause the error, because it is not acceptable by **C**. But I am still not sure how to pass the value from `zmqpp::message` to `char*`. All the ways that I tried caused some syntax error.

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
