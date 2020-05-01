#include "socketWrapper.h"

void initSocket(int type) {
	context my_context;
    socket_type my_type;
    if (type == 0) {
		my_type = socket_type::req;
	} else {
		my_type = socket_type::reply;
	}
    socket socket(my_context, my_type);
    my_socket = &socket;
}

void bind(string endpoint) {
	my_socket->bind(endpoint);
}

void send(string s) {
    message message;
	message << s;
	my_socket->send(message);
}

string receive () {
	message message;
	my_socket->receive(message);
	string s;
	message >> s;
	return s;
}
