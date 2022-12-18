cmake_minimum_required(VERSION 3.23)
project(marketplace-erp-tui)

set(CMAKE_CXX_STANDARD 14)

add_executable(marketplace-erp-tui
        main.cpp
        models/supplier/Supplier.h models/supplier/Supplier.cpp
        models/client/Client.cpp models/client/Client.h
        models/order/Order.cpp models/order/Order.h
        utils/property/Property.cpp utils/property/Property.h
        utils/csvfileservices/csvfileservice/CsvFileService.cpp utils/csvfileservices/csvfileservice/CsvFileService.h
        utils/repositories/supplier-repository/SupplierRepository.cpp utils/repositories/supplier-repository/SupplierRepository.h
        utils/csvfileservices/configurationservice/ConfigurationService.cpp utils/csvfileservices/configurationservice/ConfigurationService.h
        utils/repositories/client-repository/ClientRepository.cpp utils/repositories/client-repository/ClientRepository.h
        utils/repositories/products-repository/ProductsRepository.cpp utils/repositories/products-repository/ProductsRepository.h
        )
