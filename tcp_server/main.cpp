//
//  main.cpp
//  C++ Project
//
//  Created by Hyun Lee on 3/18/26.
//

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int argc, const char * argv[]) {
    // 1. Create a socket    
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 2. Set an socket address
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // 3. Binding
    if (bind(socket_fd, (sockaddr*)&address, sizeof(address)) == -1) {
        std::cerr << "failed to bind socket" << std::endl;
        return 1;
    }

    std::cout << "Socket created and bound to port 8080" << std::endl;

    // 4. Listen for incoming connections
    if (listen(socket_fd, 5) == -1) {
        std::cerr << "failed to listen for incoming connections" << std::endl;
        return 1;
    }

    std::cout << "Listening for incoming connections..." << std::endl;

    // 5. Close the socket
    close(socket_fd);
    
    return 0;
}
