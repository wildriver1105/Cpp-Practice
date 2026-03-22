# 1. 최소 요구 버전 설정
cmake_minimum_required(VERSION 3.10)

# 2. 프로젝트 이름과 언어 설정
project(TcpServer VERSION 1.0 LANGUAGES CXX)

# 3. C++ 표준 설정 (어제 사용한 -std=c++17 대응)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 실행 파일 생성 및 포함될 소스 파일들 명시
# 이제 clang++ 뒤에 일일이 적던 파일들을 여기에 적습니다.
add_executable(server 
    main.cpp 
    Socket.cpp
)