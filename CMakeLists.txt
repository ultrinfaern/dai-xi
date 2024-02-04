cmake_minimum_required(VERSION 3.27)
project(xi)

set(CMAKE_CXX_STANDARD 23)

add_library(xi SHARED
        xi.cpp
        xi_xi.h
        xi_xi.cpp
        xi_log.cpp
        xi_log.h
        xi_fun.cpp
        xi_fun.h)
