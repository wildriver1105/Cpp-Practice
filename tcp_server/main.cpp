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
        std::cerr << "Failed to bind socket to port 8080" << std::endl << strerror(errno);
        return 1;
    }

    server.listen();
    std::cout << "Socket bound to port 8080" << std::endl;

    while (true) {
        int client_fd = server.accept();
        if (client_fd == -1) continue;

        std::cout << "Client connected! fd: " << client_fd << std::endl;
    
        char buffer[1024] = {0};
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0) {
            std::cout << "Message from client: " << buffer << std::endl;

            const char* response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "Content-Length: 50\r\n"
                "Connection: close\r\n"
                "\r\n"
                "<html><body><h1>C++ Server Online!</h1></body></html>";

            write(client_fd, response, strlen(response));
        }

        close(client_fd);
        std::cout << "Client disconnected! fd: " << client_fd << std::endl;
    }
    
    return 0;
}
