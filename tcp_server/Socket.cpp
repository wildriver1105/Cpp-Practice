#include "Socket.hpp"
#include <unistd.h>
#include <iostream>

Socket::Socket() {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
    }
}

Socket::~Socket() {
    if (socket_fd != -1) {
        close(socket_fd);
        std::cerr << "Socket " << socket_fd << " is being closed" << std::endl;
    }
}

bool Socket::bind(int port) {
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (::bind(socket_fd, (struct sockaddr*)&address, sizeof(address)) == -1) {
        return false;
    }
    return true;
}

void Socket::listen() {
    ::listen(socket_fd, 5);
}