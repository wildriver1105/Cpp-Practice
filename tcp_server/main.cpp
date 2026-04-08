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

int main() {
    Socket server;
    if (!server.bind(8080)) return 1;
    server.listen();

    std::cout << "🚀 CTO's Engine starts on port 8080..." << std::endl;

    while (true) {
        int client_fd = server.accept();
        if (client_fd == -1) continue;

        char buffer[2048] = {0}; // 어제 배운 '고정 버퍼' 방식
        ssize_t bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);

        if (bytes_read > 0) {
            // [1] 요청 해석 (L7 Parsing)
            HttpRequest request;
            request.parse(buffer);

            // [2] 응답 객체 생성 및 로직 처리
            HttpResponse response;
            std::string path = request.getPath();

            if (path == "/") {
                response.setStatusCode(200);
                response.setBody("<h1>Ship's Log: Day 1</h1><p>System Layer: Online</p>");
            } else if (path == "/status") {
                response.setStatusCode(200);
                response.setBody("<h1>System Status</h1><p>NMEA2000: Ready<p>GPS: Fixed</p>");
            } else {
                response.setStatusCode(404);
                response.setBody("<h1>404: Port Not Found</h1>");
            }

            // [3] 최종 규격 조립 및 전송 (Serialization & Transmission)
            std::string raw_response = response.toString();
            write(client_fd, raw_response.c_str(), raw_response.length());
        }
        close(client_fd);
    }
    return 0;
}
