cmake_minimum_required(VERSION 3.23)
project(marketplace-erp-tui)

set(CMAKE_CXX_STANDARD 14)

add_executable(marketplace-erp-tui
        main.cpp
        public-entities/supplier/Supplier.h public-entities/supplier/Supplier.cpp
        public-entities/client/Client.cpp public-entities/client/Client.h
        public-entities/order/Order.cpp public-entities/order/Order.h
        public-entities/product/Product.cpp public-entities/product/Product.h
        public-entities/category/Category.cpp public-entities/category/Category.h
)
