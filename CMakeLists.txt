cmake_minimum_required(VERSION 3.12)
project(syslogudp)

set(CMAKE_CXX_STANDARD 14)
set(Boost_USE_STATIC_LIBS   ON)
find_package(Boost  REQUIRED system program_options regex)

add_executable(syslogudp main.cpp)
target_link_libraries(syslogudp ${Boost_LIBRARIES})