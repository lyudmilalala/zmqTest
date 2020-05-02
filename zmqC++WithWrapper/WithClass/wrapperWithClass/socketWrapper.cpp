#include "socketWrapper.h"

ZMQSocket::ZMQSocket(int type) : my_socket(my_context, socket_type::reply) {
    if (type == 0) {
		my_type = socket_type::req;
	} else {
		my_type = socket_type::reply;
	}
    my_socket=socket(my_context, my_type);
    // my_socket(my_context, my_type);

}

ZMQSocket::~ZMQSocket(void){}

void ZMQSocket::bind(string endpoint) {
	my_socket.bind(endpoint);
	// my_socket->bind(endpoint);
}

void ZMQSocket::send(string s) {
    message message;
	message << s;
	my_socket.send(message);
	// my_socket->send(message);
}

string ZMQSocket::receive () {
	message message;
	my_socket.receive(message);
	// my_socket->receive(message);
	string s;
	message >> s;
	return s;
}