//
//  main.cpp
//  C++ Project
//
//  Created by Hyun Lee on 3/18/26.
//

#include <iostream>
#include "Socket.hpp"

int main(int argc, const char * argv[]) {
    // 1. Create a socket
    Socket server;

    // 2. Bind the socket to the port
    if (!server.bind(8080)) {
        std::cerr << "Failed to bind socket to port 8080" << std::endl;
        return 1;
    }
    std::cout << "Socket bound to port 8080" << std::endl;

    // 3. Listen for incoming connections
    server.listen();
    std::cout << "Listening for incoming connections..." << std::endl;
    
    return 0;
}
