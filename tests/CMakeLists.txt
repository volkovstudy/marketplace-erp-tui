cmake_minimum_required(VERSION 3.23)
project(marketplace-erp-tui-tests)

set(CMAKE_CXX_STANDARD 14)

add_executable(marketplace-erp-tui-tests
        main.cpp
        CsvFileServiceTest.h
        SupplierRepositoryTest.h
        ConfigurationServiceTest.h
        ClientRepositoryTest.h
        ProductsRepositoryTest.h
        OrderRepositoryTest.h
        ../models/supplier/Supplier.h ../models/supplier/Supplier.cpp
        ../models/client/Client.cpp ../models/client/Client.h
        ../models/order/Order.cpp ../models/order/Order.h
        ../utils/property/Property.cpp ../utils/property/Property.h
        ../utils/csvfileservices/csvfileservice/CsvFileService.cpp ../utils/csvfileservices/csvfileservice/CsvFileService.h
        ../utils/repositories/supplier-repository/SupplierRepository.cpp ../utils/repositories/supplier-repository/SupplierRepository.h
        ../utils/csvfileservices/configurationservice/ConfigurationService.cpp ../utils/csvfileservices/configurationservice/ConfigurationService.h
        ../utils/repositories/client-repository/ClientRepository.cpp ../utils/repositories/client-repository/ClientRepository.h
        ../utils/repositories/order-repository/OrderRepository.cpp ../utils/repositories/order-repository/OrderRepository.h
        ../utils/repositories/products-repository/ProductsRepository.cpp ../utils/repositories/products-repository/ProductsRepository.h
        )
