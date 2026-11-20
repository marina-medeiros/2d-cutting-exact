cmake_minimum_required(VERSION 3.10)
project(2d-cutting-exact CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Threads REQUIRED)
find_package(OpenMP)

add_executable(dbpb
    src/main_dbpb.cpp
    src/matriz.cpp
    src/instancia_db.cpp
    src/variaveis.cpp
    src/conflitos.cpp
    src/dbpb.cpp
    src/dbpb_lb.cpp
    src/grid.cpp
    src/molde.cpp
    src/io.cpp
    src/empacotador.cpp
    src/conversor.cpp
)

target_include_directories(dbpb PRIVATE include)
target_link_libraries(dbpb PRIVATE Threads::Threads)

if(OpenMP_CXX_FOUND)
    target_link_libraries(dbpb PRIVATE OpenMP::OpenMP_CXX)
endif()
