cmake_minimum_required(VERSION 3.14)
project(temp)

set(CMAKE_CXX_STANDARD 14)

add_executable(temp main.cpp Date.cpp Date.h Employee.cpp Employee.h manager.cpp manager.h salesman.cpp salesman.h salesmanager.cpp salesmanager.h technician.cpp technician.h)