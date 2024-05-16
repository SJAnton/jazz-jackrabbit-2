cmake_minimum_required(VERSION 3.10)
project(client)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# Common source files
file(GLOB COMMON_SOURCES 
    "../common_*.cpp"
)

# Client source files
file(GLOB CLIENT_SOURCES 
    "../client_main.cpp"
    "../client_game.cpp"
    "../client_protocol.cpp"
    "../client_receiver.cpp"
    "../client_sender.cpp"
    "../interfaz_grafica.cpp"
    "../spritesheet.cpp"
    "../sprite_object.cpp"
)

# Server source files
file(GLOB SERVER_SOURCES 
    "../server_dummy.cpp"
)

# Client executable
add_executable(client ${CLIENT_SOURCES} ${COMMON_SOURCES})
target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} pthread)

# Server executable
add_executable(server ${SERVER_SOURCES} ${COMMON_SOURCES})
