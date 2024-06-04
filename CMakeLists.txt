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
    "client_src/client_main.cpp"
    "client_src/client_player.cpp"
    "client_src/client_protocol.cpp"
    "client_src/client_receiver.cpp"
    "client_src/client_sender.cpp"
    "client_src/interfaz_grafica.cpp"
    "client_src/spritesheet.cpp"
    "client_src/sprite_object.cpp"
    "client_src/spritesheetPlayer.cpp"
    "client_src/spritesManager.cpp"
    "client_src/client_renderer.cpp"
    "client_src/event_handler.cpp"
    "client_src/sprite_player.cpp"
    "client_src/sprites_players.cpp"
    "client_src/characters.cpp"
)

# Server source files
file(GLOB SERVER_SOURCES 
    "server_src/*.cpp"
)


find_package(SDL2 REQUIRED)  # Busca SDL2

include_directories(${SDL2_INCLUDE_DIRS})

# Client executable
add_executable(client ${CLIENT_SOURCES} ${COMMON_SOURCES})

target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} pthread)

# Server executable
add_executable(server ${SERVER_SOURCES} ${COMMON_SOURCES})
