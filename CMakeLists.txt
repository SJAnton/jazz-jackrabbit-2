cmake_minimum_required(VERSION 3.10)
project(client)

set(CMAKE_CXX_STANDARD 17)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# Common source files
file(GLOB COMMON_SOURCES 
    "common_src/*.cpp"
    
)

# Client source files
file(GLOB CLIENT_SOURCES
    "client_src/*.cpp"
    "client_src/interfaz_src/*.cpp"
    
)

# Server source files
file(GLOB SERVER_SOURCES 
    "_server_src/*.cpp"
)


find_package(SDL2 REQUIRED)  # Busca SDL2

include_directories(${SDL2_INCLUDE_DIRS})

# Client executable
add_executable(client ${CLIENT_SOURCES} ${COMMON_SOURCES})

target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} pthread)

# Server executable
add_executable(server ${SERVER_SOURCES} ${COMMON_SOURCES})
