set(
    LIBRARY_SOURCES
    src/models/Client.cpp
    src/models/Order.cpp
    src/models/Product.cpp
    src/models/Property.cpp
    src/file-services/CsvFileService.cpp
    src/file-services/ConfigurationService.cpp
    src/repositories/ClientRepository.cpp
    src/repositories/ProductsRepository.cpp
    src/repositories/OrderRepository.cpp
    src/table-printer/TablePrinter.cpp
    src/program-launcher/ProgramLauncher.cpp
    src/program-launcher/dialogues/client/ClientDialog.cpp
    src/program-launcher/dialogues/client/ClientAddingDialog.cpp
    src/program-launcher/dialogues/order/OrdersDialog.cpp
    src/program-launcher/dialogues/order/OrderAddingDialog.cpp
    src/utils/Utils.cpp
)

add_library(marketplace_erp_tui_lib ${LIBRARY_SOURCES})

target_include_directories(marketplace_erp_tui_lib PUBLIC include)
