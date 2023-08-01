cmake_minimum_required(VERSION 3.5)
project(pie LANGUAGES C)

# Specify the include directories for GD
include_directories(/usr/include)

# Specify the library directories for GD
link_directories(/usr/lib/x86_64-linux-gnu)

add_executable(pie main.c)
target_link_libraries(pie gd m)

install(TARGETS pie
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
