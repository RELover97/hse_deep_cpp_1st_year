cmake_minimum_required(VERSION 3.16)

project(wallet_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include(FetchContent)

# FetchContent_Declare(
#     fmt
#     GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#     GIT_TAG 12.2.0
# )

# FetchContent_MakeAvailable(fmt)

find_package(fmt CONFIG REQUIRED)

add_library(wallet
    src/wallet.cpp
)

target_include_directories(wallet
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Now fmt::fmt is linked privately as we have header-only lib wallet_format for wallet_demo
target_link_libraries(wallet PRIVATE fmt::fmt)


# header-only lib

add_library(wallet_format INTERFACE)

target_include_directories(wallet_format INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(wallet_format INTERFACE fmt::fmt)



add_executable(wallet_demo
    src/main.cpp
)

target_link_libraries(wallet_demo PRIVATE wallet)

# usage of header-only lib
target_link_libraries(wallet_demo PRIVATE wallet_format)