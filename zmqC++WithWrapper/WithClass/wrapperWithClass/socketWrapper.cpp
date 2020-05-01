#include "socketWrapper.h"

ZMQSocket::ZMQSocket(int type) {
    if (type == 0) {
		my_type = socket_type::req;
	} else {
		my_type = socket_type::reply;
	}
    socket socket(my_context, my_type);
    my_socket = &socket;

}

ZMQSocket::~ZMQSocket(void){}

void ZMQSocket::bind(string endpoint) {
	my_socket->bind(endpoint);
}

void ZMQSocket::send(string s) {
    message message;
	message << s;
	my_socket->send(message);
}

string ZMQSocket::receive () {
	message message;
	my_socket->receive(message);
	string s;
	message >> s;
	return s;
}