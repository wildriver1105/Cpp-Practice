#include "HttpRequest.hpp"

HttpRequest::HttpRequest() : method_(""), path_(""), version_("") {}

void HttpRequest::parse(const std::string& raw_request) {
    // 1. 첫 번째 줄(Request Line) 위치 찾기
    size_t line_end = raw_request.find("\r\n");
    if (line_end == std::string::npos) return;

    std::string first_line = raw_request.substr(0, line_end);

    // 2. 공백을 기준으로 Method, Path, Version 분리
    // [직관 체크] 이 과정은 메모리 상의 텍스트 더미에서 특정 패턴을 찾는 '패턴 매칭'입니다.
    size_t first_space = first_line.find(" ");
    size_t second_space = first_line.find(" ", first_space + 1);

    if (first_space != std::string::npos && second_space != std::string::npos) {
        method_ = first_line.substr(0, first_space);
        path_ = first_line.substr(first_space + 1, second_space - first_space - 1);
        version_ = first_line.substr(second_space + 1);
    }
}

std::string HttpRequest::getMethod() const { return method_; }
std::string HttpRequest::getPath() const { return path_; }