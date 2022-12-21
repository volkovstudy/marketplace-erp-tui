cmake_minimum_required(VERSION 3.23)
project(marketplace-erp-tui)

set(CMAKE_CXX_STANDARD 14)

add_executable(marketplace-erp-tui
        main.cpp
        src/models/client/Client.cpp src/models/client/Client.h
        src/models/order/Order.cpp src/models/order/Order.h
        src/models/property/Property.cpp src/models/property/Property.h
        src/file-services/csv-file-service/CsvFileService.cpp src/file-services/csv-file-service/CsvFileService.h
        src/file-services/configuration-service/ConfigurationService.cpp src/file-services/configuration-service/ConfigurationService.h
        src/repositories/client-repository/ClientRepository.cpp src/repositories/client-repository/ClientRepository.h
        src/repositories/products-repository/ProductsRepository.cpp src/repositories/products-repository/ProductsRepository.h
        src/program-launcher/ProgramLauncher.cpp src/program-launcher/ProgramLauncher.h
        )
