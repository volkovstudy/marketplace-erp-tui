cmake_minimum_required(VERSION 3.23)
project(marketplace-erp-tui)

set(CMAKE_CXX_STANDARD 14)

add_executable(marketplace-erp-tui
        main.cpp
        models/client/Client.cpp models/client/Client.h
        models/order/Order.cpp models/order/Order.h
        models/property/Property.cpp models/property/Property.h
        file-services/csv-file-service/CsvFileService.cpp file-services/csv-file-service/CsvFileService.h
        file-services/configurationservice/ConfigurationService.cpp file-services/configurationservice/ConfigurationService.h
        repositories/client-repository/ClientRepository.cpp repositories/client-repository/ClientRepository.h
        repositories/products-repository/ProductsRepository.cpp repositories/products-repository/ProductsRepository.h
        )
