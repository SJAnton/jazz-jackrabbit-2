cmake_minimum_required(VERSION 3.10)
project(client)

set(CMAKE_CXX_STANDARD 17)

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
    #"_server_src/*.cpp"
)

# Client executable
add_executable(client ${CLIENT_SOURCES} ${COMMON_SOURCES})
target_link_libraries(client ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} pthread)

# Ensure dependencies are built before client
if (TARGET sdl2_dependency)
    add_dependencies(client sdl2_dependency)
endif()

if (TARGET sdl2_image_dependency)
    add_dependencies(client sdl2_image_dependency)
endif()

# Custom clean target
add_custom_target(clean-all
  COMMAND ${CMAKE_BUILD_TOOL} clean
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
)
