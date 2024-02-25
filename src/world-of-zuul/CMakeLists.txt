
# Define the project name
project(world_of_zuul)

# Set the cmake minimum version to 3.5.1
cmake_minimum_required(VERSION 3.5.1)

# cache variable that determines whether SDL should be included
set(TERMINAL_ONLY OFF CACHE BOOL "if the application should not be run using SDL")

if(TERMINAL_ONLY)
    add_compile_definitions(TERMINAL_ONLY)
endif()

# tell preprocessor if projekt should only be run in terminal or not

# Add SDL2 CMake modules
if(NOT TERMINAL_ONLY)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
endif()

# Add all c++ source files under the src directory
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wextra -pedantic>)

# Only add SDL libarries if TERMINAL_ONLY is false
if(NOT TERMINAL_ONLY)
    # Add SDL2 library
    find_package(SDL2 REQUIRED)
    target_link_libraries(${PROJECT_NAME} SDL2::Main)

    # Add SDL2_image library
    #find_package(SDL2_image REQUIRED)
    #target_link_libraries(${PROJECT_NAME} SDL2::Image)

    # Add SDL2_ttf library
    #find_package(SDL2_ttf REQUIRED)
    #target_link_libraries(${PROJECT_NAME} SDL2::TTF)

    # Add SDL2_net library
    #find_package(SDL2_net REQUIRED)
    #target_link_libraries(${PROJECT_NAME} SDL2::Net)

    # Add SDL2_mixer library
    #find_package(SDL2_mixer REQUIRED)
    #target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

    # Add SDL2_gfx library
    #find_package(SDL2_gfx REQUIRED)
    #target_link_libraries(${PROJECT_NAME} SDL2::GFX)
endif()
