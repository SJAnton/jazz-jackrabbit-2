cmake_minimum_required(VERSION 3.10)

project(client VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Flags de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

include(FindPkgConfig)
include(ExternalProject)

# Function to set variables for SDL2 and SDL2_image
function(set_sdl_variables)
    include_directories(${SDL2_INCLUDE_DIRS})
    link_directories(${SDL2_LIBRARY_DIRS})
endfunction()

# Check for SDL2
pkg_check_modules(SDL2 REQUIRED sdl2)
if(NOT SDL2_FOUND)
    ExternalProject_Add(SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-2.26.5
        PREFIX ${CMAKE_BINARY_DIR}/SDL2
        CONFIGURE_COMMAND ./configure
        BUILD_COMMAND make
        INSTALL_COMMAND make install
        BUILD_IN_SOURCE 1
    )
    set(SDL2_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/SDL2/src/SDL2-build/include")
    set(SDL2_LIBRARY_DIRS "${CMAKE_BINARY_DIR}/SDL2/src/SDL2-build/lib")
    set(SDL2_LIBRARIES SDL2)
    add_custom_target(sdl2_dependency DEPENDS SDL2)
else()
    set_sdl_variables()
endif()

# Check for SDL2_image
pkg_check_modules(SDL2IMAGE REQUIRED SDL2_image)
if(NOT SDL2IMAGE_FOUND)
    ExternalProject_Add(SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG release-2.6.3
        PREFIX ${CMAKE_BINARY_DIR}/SDL2_image
        CONFIGURE_COMMAND ./configure
        BUILD_COMMAND make
        INSTALL_COMMAND make install
        BUILD_IN_SOURCE 1
    )
    set(SDL2IMAGE_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/SDL2_image/src/SDL2_image-build/include")
    set(SDL2IMAGE_LIBRARY_DIRS "${CMAKE_BINARY_DIR}/SDL2_image/src/SDL2_image-build/lib")
    set(SDL2IMAGE_LIBRARIES SDL2_image)
    add_custom_target(sdl2_image_dependency DEPENDS SDL2_image)
else()
    set_sdl_variables()
endif()

# cmake . genera el makefile
# make -f Makefile ejecuta el makefile
set(SOURCE_FILES
    ../../common_src/info_juego.cpp
    ../../common_src/liberror.cpp
    ../../common_src/protocol.cpp
    ../../common_src/resolver.cpp
    ../../common_src/resolvererror.cpp
    ../../common_src/socket.cpp

    ../client_main.cpp
    ../client_player.cpp
    ../client_protocol.cpp
    ../client_receiver.cpp
    ../client_renderer.cpp
    ../client_sender.cpp

    ../interfaz_src/button_character.cpp
    ../interfaz_src/button_partida.cpp
    ../interfaz_src/characters.cpp
    ../interfaz_src/event_handler.cpp
    ../interfaz_src/fontManager.cpp
    ../interfaz_src/interfaz_grafica.cpp
    ../interfaz_src/sprite_object.cpp
    ../interfaz_src/sprite_player.cpp
    ../interfaz_src/spritesheet.cpp
    ../interfaz_src/spritesManager.cpp
    ../interfaz_src/sprites_players.cpp
)

add_executable(client ${SOURCE_FILES})

target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} pthread)
