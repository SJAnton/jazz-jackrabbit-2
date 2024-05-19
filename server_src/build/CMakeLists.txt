cmake_minimum_required(VERSION 3.10)

project(server VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Flags de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

add_subdirectory(yaml-cpp)

include_directories(yaml-cpp/include)

# cmake . genera el makefile
# make -f Makefile ejecuta el makefile
set(SOURCE_FILES
    # Archivos common
    ../common_liberror.cpp
    ../common_resolver.cpp
    ../common_resolvererror.cpp
    ../common_socket.cpp

    # Archivos server
    ../server_app.cpp
    ../server_client.cpp
    ../server_config_reader.cpp
    ../server_gameloop.cpp
    ../server_main.cpp
    ../server_protocol.cpp
    ../server_queue_list.cpp
    ../server_receiver.cpp
    ../server_sender.cpp

    # Armas
    ../weapons/server_blaster.cpp
    ../weapons/server_bouncer.cpp
    ../weapons/server_electro_blaster.cpp
    ../weapons/server_freezer.cpp
    ../weapons/server_pepper_spray.cpp
    ../weapons/server_rf_missile.cpp
    ../weapons/server_seeker.cpp
    ../weapons/server_toaster.cpp

    # Proyectiles
    ../weapons/projectile/server_iceball.cpp
    ../weapons/projectile/server_projectile.cpp
    ../weapons/projectile/server_rocket.cpp
    ../weapons/projectile/server_seeker_rocket.cpp

    # Personajes
    ../characters/server_character.cpp
    ../characters/server_enemy.cpp
    ../characters/server_player_jazz.cpp
    ../characters/server_player_lori.cpp
    ../characters/server_player_spaz.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} yaml-cpp)
