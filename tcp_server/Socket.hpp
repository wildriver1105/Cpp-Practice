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
        int accept();

    private:
        int socket_fd;
};

#endif