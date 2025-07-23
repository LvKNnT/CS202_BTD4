cmake_minimum_required(VERSION 3.16)
project(CS202_BTD4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(Game ${SOURCES})

target_include_directories(Game PRIVATE 
    src
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(Game PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib/libraylib.a 
    gdi32 winmm opengl32
)
