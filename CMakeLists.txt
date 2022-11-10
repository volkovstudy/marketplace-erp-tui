cmake_minimum_required(VERSION 3.23)
project(marketplace-erp-tui)

set(CMAKE_CXX_STANDARD 14)

add_executable(marketplace-erp-tui main.cpp public-entities/supplier/Supplier.h public-entities/supplier/Supplier.cpp)
