cmake_minimum_required(VERSION 3.23)
project(marketplace-erp-tui-tests)

set(CMAKE_CXX_STANDARD 14)

add_executable(marketplace-erp-tui-tests
        main.cpp
        CsvFileServiceTest.h
        ConfigurationServiceTest.h
        ClientRepositoryTest.h
        ProductsRepositoryTest.h
        OrderRepositoryTest.h
        ../models/client/Client.cpp ../models/client/Client.h
        ../models/order/Order.cpp ../models/order/Order.h
        ../models/property/Property.cpp ../models/property/Property.h
        ../utils/csvfileservices/csvfileservice/CsvFileService.cpp ../utils/csvfileservices/csvfileservice/CsvFileService.h
        ../utils/csvfileservices/configurationservice/ConfigurationService.cpp ../utils/csvfileservices/configurationservice/ConfigurationService.h
        ../repositories/client-repository/ClientRepository.cpp ../repositories/client-repository/ClientRepository.h
        ../repositories/order-repository/OrderRepository.cpp ../repositories/order-repository/OrderRepository.h
        ../repositories/products-repository/ProductsRepository.cpp ../repositories/products-repository/ProductsRepository.h
        )
