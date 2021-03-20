cmake_minimum_required(VERSION 3.7)
project(url_shortener)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(Threads REQUIRED)
find_package(libpqxx REQUIRED)
find_package(PostgreSQL REQUIRED)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(url_shortener ${SOURCES})
target_link_libraries(url_shortener ${Boost_LIBRARIES} Threads::Threads libpqxx::pqxx_shared ${PostgreSQL_LIBRARIES})
target_include_directories(url_shortener PRIVATE ${Boost_INCLUDE_DIRS} src)