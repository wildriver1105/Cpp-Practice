//
//  main.cpp
//  C++ Project
//
//  Created by Hyun Lee on 3/18/26.
//

#include <iostream>
#include <unistd.h>
#include "Socket.hpp"
#include "HttpRequest.hpp"

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
            HttpRequest req;
            req.parse(buffer);

            std::string method = req.getMethod();
            std::string path = req.getPath();

            std::cout << "[요청 발생] Method: " << method << ", Path: " << path << std::endl;

            std::string response_body;

            if (path == "/") {
                response_body = "<html><body><h1>C++ Server Online!</h1></body></html>";
            } else if (path == "/hello") {
                response_body = "<html><body><h1>Hello, World!</h1></body></html>";
            } else {
                response_body = "<html><body><h1>404 Not Found</h1></body></html>";
            }

            std::string response = 
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html; charset=UTF-8\r\n"
                "Content-Length: " + std::to_string(response_body.length()) + "\r\n"
                "Connection: close\r\n"
                "\r\n" + response_body;

            write(client_fd, response.c_str(), response.length());
        }

        close(client_fd);
    }
    
    return 0;
}
