cmake_minimum_required(VERSION 3.10)

project(client VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Flags de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-unused-private-field")

# cmake . genera el makefile
# make -f Makefile ejecuta el makefile
set(SOURCE_FILES
    ../../common_src/liberror.cpp
    ../../common_src/resolver.cpp
    ../../common_src/resolvererror.cpp
    ../../common_src/socket.cpp

    ../client_dummy_main.cpp
    ../client_dummy_protocol.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
