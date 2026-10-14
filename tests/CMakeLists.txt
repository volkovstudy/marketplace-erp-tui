include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP ON
        FIND_PACKAGE_ARGS NAMES GTest
)

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        marketplace-erp-tui-tests
        client-repository-test.cpp
        configuration-service-test.cpp
        csv-file-service-test.cpp
        order-repository-test.cpp
        products-repository-test.cpp
        table-printer-test.cpp
)

target_link_libraries(marketplace-erp-tui-tests
        marketplace_erp_tui_lib
        GTest::gtest_main
        GTest::gmock_main
)

include(GoogleTest)

gtest_discover_tests(marketplace-erp-tui-tests)
