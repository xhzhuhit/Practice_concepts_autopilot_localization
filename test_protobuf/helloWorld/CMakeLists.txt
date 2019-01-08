cmake_minimum_required(VERSION 2.8)
project(test_protobuf)

add_definitions(-std=c++11)

find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
    message(STATUS "protibuf library found")
else()
    message(FATAL_ERROR "protobuf library is needed but not found")
endif()

add_executable(testProtobuf 
        proto/hello.pb.cc
        src/testProtobuf.cpp)
target_link_libraries(testProtobuf
        ${PROTOBUF_LIBRARIES})
