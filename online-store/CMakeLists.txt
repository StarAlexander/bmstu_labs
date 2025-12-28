cmake_minimum_required(VERSION 3.14)
project(online_store)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include_directories(include)


find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)


include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})


file(GLOB SOURCES "src/*.cpp")


add_executable(main ${SOURCES})


target_link_libraries(main ${PQXX_LIBRARIES} pq)