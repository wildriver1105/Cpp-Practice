#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>

class Socket {
    public:
        Socket();
        ~Socket();

        bool bind(int port);
        void listen();

    private:
        int socket_fd;
};

#endif