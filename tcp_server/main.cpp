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
#include "HttpResponse.hpp"

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
            } else if (path == "/cto") {
                response_body = "<h1>CTO's Vision</h1><p>The right spec is a balance of art and science.</p>";
            } else {
                response_body = "<h1>404 Not Found</h1>";
            }

            HttpResponse res;
            
            res.setStatusCode(200);
            res.setContentType("text/html");
            res.setBody(response_body);

            // 최종 문자열 생성 및 전송
            std::string raw_res = res.toString();
            write(client_fd, raw_res.c_str(), raw_res.length());
        }

        close(client_fd);
    }
    
    return 0;
}
