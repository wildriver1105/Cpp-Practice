#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <string>
#include <map>

class HttpResponse {
    public:
        HttpResponse();

        void setStatusCode(int code);
        void setContentType(const std::string& type);
        void setBody(const std::string& body);

        std::string toString() const;
    
    private:
        int statusCode_;
        std::string contentType_;
        std::string body_;

        std::string getStatusMessage(int code) const;
};

#endif