//
//  main.cpp
//  C++ Project
//
//  Created by Hyun Lee on 3/18/26.
//

#include <iostream>
#include <unistd.h>
#include "Socket.hpp"

int main(int argc, const char * argv[]) {
    Socket server;

    if (!server.bind(8080)) {
        std::cerr << "Failed to bind socket to port 8080" << std::endl;
        return 1;
    }

    server.listen();
    std::cout << "Socket bound to port 8080" << std::endl;

    int client_fd = server.accept();

    if (client_fd != -1) {
        std::cout << "Client connected! fd: " << client_fd << std::endl;

        char buffer[1024] = {0};
        read(client_fd, buffer, 1024);
        std::cout << "Message from client: " << buffer << std::endl;

        const char* msg = "HTTP/1.1 200 OK\r\nContent-Length: 12\r\n\r\nHello, World!";
        write(client_fd, msg, strlen(msg));

        close(client_fd);
    }
    
    return 0;
}
