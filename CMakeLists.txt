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
        xi_fun.h
        xi_cfg.cpp
        xi_cfg.h
        xi_guard.cpp
        xi_guard.h)

set_target_properties (xi PROPERTIES PREFIX "" OUTPUT_NAME "XInput9_1_0" SUFFIX ".dll")
