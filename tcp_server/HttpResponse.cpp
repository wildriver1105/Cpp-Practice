#include "HttpResponse.hpp"

HttpResponse::HttpResponse() : statusCode_(200), contentType_("text/html") {}

void HttpResponse::setStatusCode(int code) { statusCode_ = code;}
void HttpResponse::setContentType(const std::string& type) { contentType_ = type; }
void HttpResponse::setBody(const std::string& body) { body_ = body;}

std::string HttpResponse::getStatusMessage(int code) const {
    if (code == 200) return "OK";
    if (code == 404) return "Not Found";
    return "Unknown";
}

std::string HttpResponse::toString() const {
    std::string res = "HTTP/1.1 " + std::to_string(statusCode_) + " " + getStatusMessage(statusCode_) + "\r\n";

    res += "Content-Type: " + contentType_ + "; charset=UTF-8\r\n";
    res += "Content-Length: " + std::to_string(body_.length()) + "\r\n";
    res += "Connection: close\r\n";

    res += "\r\n";

    res += body_;

    return res;
}