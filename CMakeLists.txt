cmake_minimum_required(VERSION 3.25)
project(spotify_api)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(spotify_api main.cpp api/SpotifyAPI.cpp)

include_directories(/usr/include/x86_64-linux-gnu/curl)

target_link_libraries(spotify_api curl)

