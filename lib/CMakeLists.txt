set(
    LIBRARY_SOURCES
    src/models/client/Client.cpp
    src/models/order/Order.cpp
    src/models/product/Product.cpp
    src/models/property/Property.cpp
    src/file-services/csv-file-service/CsvFileService.cpp
    src/file-services/configuration-service/ConfigurationService.cpp
    src/repositories/client-repository/ClientRepository.cpp
    src/repositories/products-repository/ProductsRepository.cpp
    src/repositories/order-repository/OrderRepository.cpp
    src/table-printer/TablePrinter.cpp
    src/program-launcher/ProgramLauncher.cpp
    src/program-launcher/dialogues/client-dialog/ClientDialog.cpp
    src/utils/Utils.cpp
    src/program-launcher/dialogues/orders-dialog/OrdersDialog.cpp
    src/program-launcher/dialogues/client-dialog/client-adding-dialog/ClientAddingDialog.cpp
    src/program-launcher/dialogues/orders-dialog/order-adding-dialog/OrderAddingDialog.cpp
)

add_library(marketplace_erp_tui_lib ${LIBRARY_SOURCES})

target_include_directories(marketplace_erp_tui_lib PUBLIC include)
