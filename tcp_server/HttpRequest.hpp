#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <string>
#include <iostream>

class HttpRequest {
    public:
        HttpRequest();

        void parse(const std::string& request);

        std::string getMethod() const;
        std::string getPath() const;
    
    private:
        std::string method_;
        std::string path_;
        std::string version_;
};

#endif