# Specifica la versione minima di CMake
cmake_minimum_required(VERSION 3.10)

# Nome del progetto
project(Snap7Project)

# Abilita il supporto per C++11
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(snap7)

add_executable(client client.cpp)
add_executable(server server.cpp)
target_link_libraries(client PUBLIC snap7)
target_link_libraries(server PUBLIC snap7)

INSTALL ( TARGETS client
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION bin
    LIBRARY DESTINATION bin
)