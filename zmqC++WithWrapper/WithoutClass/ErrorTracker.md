Error Tracker
======================================
## Description ##
This is an implementation of ZMQ messager in **C++** with `zmqpp` library.

This case is written to test whether a zmqpp function wrapper can work properly in a C++ program, as they have the same language.

The wrapper `.cpp` contains:
* A zmqpp::socket
* A initialization function for the socket
* A binding function to bind the socket with an endpoint
* A sending function
* A receiving function

## Compile and Running Status ##
Error for compiling: 
```
# g++ -g wrapperWithoutClass/socketWrapper.cpp server.cpp -o server -std=c++11 -lzmq /usr/local/lib/libzmqpp.a
wrapperWithoutClass/socketWrapper.cpp: In function ‘void initSocket(int)’:
wrapperWithoutClass/socketWrapper.cpp:11:34: error: no match for call to ‘(zmqpp::socket) (zmqpp::context&, zmqpp::socket_type&)’
     my_socket(my_context, my_type);
                                  ^
```
```
In file included from /usr/local/include/zmqpp/message.hpp:21,
                 from /usr/local/include/zmqpp/zmqpp.hpp:64,
                 from wrapperWithoutClass/socketWrapper.h:4,
                 from server.cpp:3:
/usr/include/c++/8/functional: In substitution of ‘template<class _Functor, class ... _Bound_args> template<class _Fn, class _CallArgs, class ... _BArgs> using _Res_type_impl = typename std::result_of<_Fn&(std::_Bind<_Functor(_Bound_args ...)>::_Mu_type<_BArgs, _CallArgs>&& ...)>::type [with _Fn = const char*; _CallArgs = _CallArgs; _BArgs = {}; _Functor = const char*; _Bound_args = {}]’:
/usr/include/c++/8/functional:447:71:   required from ‘struct std::_Bind<const char*()>’
server.cpp:16:22:   required from here
/usr/include/c++/8/functional:444:72: error: no type named ‘type’ in ‘class std::result_of<const char*&()>’
    = typename result_of< _Fn&(_Mu_type<_BArgs, _CallArgs>&&...) >::type;
                                                                        ^
/usr/include/c++/8/functional: In substitution of ‘template<class _Functor, class ... _Bound_args> template<class _Fn, class _CallArgs, class ... _BArgs> using _Res_type_impl = typename std::result_of<_Fn&(std::_Bind<_Functor(_Bound_args ...)>::_Mu_type<_BArgs, _CallArgs>&& ...)>::type [with _Fn = const char*; _CallArgs = std::tuple<_Tps ...>; _BArgs = {}; _Functor = const char*; _Bound_args = {}]’:
/usr/include/c++/8/functional:447:71:   required by substitution of ‘template<class _Functor, class ... _Bound_args> template<class _CallArgs> using _Res_type = std::_Bind<_Functor(_Bound_args ...)>::_Res_type_impl<_Functor, _CallArgs, _Bound_args ...> [with _CallArgs = std::tuple<_Tps ...>; _Functor = const char*; _Bound_args = {}]’
/usr/include/c++/8/functional:480:2:   required from ‘struct std::_Bind<const char*()>’
server.cpp:16:22:   required from here
/usr/include/c++/8/functional:444:72: error: no type named ‘type’ in ‘class std::result_of<const char*&()>’

```

They happens in the function used to initialize the socket.

```
void initSocket(int type) {
	context my_context;
    socket_type my_type;
    if (type == 0) {
		my_type = socket_type::req;
	} else {
		my_type = socket_type::reply;
	}
    my_socket(my_context, my_type);
}
```

I tried to modify the way of defining the variable to:

```
void initSocket(int type) {
	context my_context;
    socket_type my_type;
    if (type == 0) {
		my_type = socket_type::req;
	} else {
		my_type = socket_type::reply;
	}
    my_socket = socket(my_context, my_type);
}
```

or

```
void initSocket(int type) {
    context my_context;
    socket_type my_type;
    if (type == 0) {
                my_type = socket_type::req;
        } else {
                my_type = socket_type::reply;
        }
    socket my_socket(my_context, my_type);
}
```

But the other error besides the pointers always exists:

```
# g++ -g wrapperWithoutClass/socketWrapper.cpp server.cpp -o server -std=c++11 -lzmq /usr/local/lib/libzmqpp.a
In file included from /usr/local/include/zmqpp/message.hpp:21,
                 from /usr/local/include/zmqpp/zmqpp.hpp:64,
                 from wrapperWithoutClass/socketWrapper.h:4,
                 from server.cpp:3:
/usr/include/c++/8/functional: In substitution of ‘template<class _Functor, class ... _Bound_args> template<class _Fn, class _CallArgs, class ... _BArgs> using _Res_type_impl = typename std::result_of<_Fn&(std::_Bind<_Functor(_Bound_args ...)>::_Mu_type<_BArgs, _CallArgs>&& ...)>::type [with _Fn = const char*; _CallArgs = _CallArgs; _BArgs = {}; _Functor = const char*; _Bound_args = {}]’:
/usr/include/c++/8/functional:447:71:   required from ‘struct std::_Bind<const char*()>’
server.cpp:16:22:   required from here
/usr/include/c++/8/functional:444:72: error: no type named ‘type’ in ‘class std::result_of<const char*&()>’
    = typename result_of< _Fn&(_Mu_type<_BArgs, _CallArgs>&&...) >::type;
                                                                        ^
/usr/include/c++/8/functional: In substitution of ‘template<class _Functor, class ... _Bound_args> template<class _Fn, class _CallArgs, class ... _BArgs> using _Res_type_impl = typename std::result_of<_Fn&(std::_Bind<_Functor(_Bound_args ...)>::_Mu_type<_BArgs, _CallArgs>&& ...)>::type [with _Fn = const char*; _CallArgs = std::tuple<_Tps ...>; _BArgs = {}; _Functor = const char*; _Bound_args = {}]’:
/usr/include/c++/8/functional:447:71:   required by substitution of ‘template<class _Functor, class ... _Bound_args> template<class _CallArgs> using _Res_type = std::_Bind<_Functor(_Bound_args ...)>::_Res_type_impl<_Functor, _CallArgs, _Bound_args ...> [with _CallArgs = std::tuple<_Tps ...>; _Functor = const char*; _Bound_args = {}]’
/usr/include/c++/8/functional:480:2:   required from ‘struct std::_Bind<const char*()>’
server.cpp:16:22:   required from here
/usr/include/c++/8/functional:444:72: error: no type named ‘type’ in ‘class std::result_of<const char*&()>’

```

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
