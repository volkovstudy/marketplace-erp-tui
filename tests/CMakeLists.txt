cmake_minimum_required(VERSION 3.23)
project(marketplace-erp-tui-tests)

set(CMAKE_CXX_STANDARD 14)

add_executable(marketplace-erp-tui-tests
        main.cpp
        CsvFileServiceTest.h
        SupplierRepositoryTest.h
        ConfigurationServiceTest.h
        ClientRepositoryTest.h
        ../public-entities/supplier/Supplier.h ../public-entities/supplier/Supplier.cpp
        ../public-entities/client/Client.cpp ../public-entities/client/Client.h
        ../public-entities/order/Order.cpp ../public-entities/order/Order.h
        ../utils/property/Property.cpp ../utils/property/Property.h
        ../utils/csvfileservices/csvfileservice/CsvFileService.cpp ../utils/csvfileservices/csvfileservice/CsvFileService.h
        ../utils/repositories/supplier-repository/SupplierRepository.cpp ../utils/repositories/supplier-repository/SupplierRepository.h
        ../utils/csvfileservices/configurationservice/ConfigurationService.cpp ../utils/csvfileservices/configurationservice/ConfigurationService.h
        ../utils/repositories/client-repository/ClientRepository.cpp ../utils/repositories/client-repository/ClientRepository.h
        ../utils/repositories/order-repository/OrderRepository.cpp ../utils/repositories/order-repository/OrderRepository.h
        )
