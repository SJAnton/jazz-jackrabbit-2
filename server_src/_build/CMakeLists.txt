cmake_minimum_required(VERSION 3.10)

project(server VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Flags de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# Instalador de yaml-cpp
include(FetchContent)

FetchContent_Declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.7.0)

FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

# cmake . genera el makefile
# make -f Makefile ejecuta el makefile
set(SOURCE_FILES
    # Archivos common
    ../../common_src/info_juego.cpp
    ../../common_src/liberror.cpp
    ../../common_src/resolver.cpp
    ../../common_src/resolvererror.cpp
    ../../common_src/socket.cpp
    ../../common_src/protocol.cpp
    ../../common_src/tile_map.cpp

    # Armas
    ../game/Weapons/weapon.cpp

    # Juego
    ../game/game.cpp
    ../game/gameloop.cpp
    ../game/game_mundo.cpp
    
    # Objetos
    ../game/GameObjects/game_object.cpp

    ../game/GameObjects/Players/game_object_player.cpp
    ../game/GameObjects/Players/player_Spaz.cpp
    ../game/GameObjects/Players/player_Lori.cpp
    ../game/GameObjects/Players/player_Jazz.cpp


    ../game/GameObjects/Collected/game_object_collected.cpp
    ../game/GameObjects/Projectile/game_object_projectile.cpp
    ../game/GameObjects/Enemies/game_object_enemy.cpp
    ../game/GameObjects/Enemies/enemy_bat.cpp
    ../game/GameObjects/Enemies/enemy_diablo.cpp
    ../game/GameObjects/Enemies/enemy_rat.cpp

    # Map
    ../game/Map/game_map.cpp
    ../game/Map/game_map_reader.cpp

    # Archivos server
    ../server_acceptor.cpp
    ../server_character_map.cpp
    ../server_client.cpp
    ../server_config_reader.cpp
    ../server_gameloop_list.cpp
    ../server_main.cpp
    ../server_protocol.cpp
    ../server_queue_list.cpp
    ../server_receiver.cpp
    ../server_sender.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp)
