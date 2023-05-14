cmake_minimum_required(VERSION 3.25)
project(spotify_api)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(spotify_api main.cpp api/SpotifyAPI.cpp entities/Album.cpp entities/Album.h entities/Track.cpp entities/Track.h entities/Artist.cpp entities/Artist.h)
add_executable(gui gui/App.cpp gui/MainFrame.cpp api/SpotifyAPI.cpp entities/Album.cpp entities/Track.cpp entities/Artist.cpp )

#include_directories(/usr/include/x86_64-linux-gnu/curl)

find_package(wxWidgets REQUIRED COMPONENTS core base)

# include curl and wxWidgets
include(${wxWidgets_USE_FILE})
include_directories(${CURL_INCLUDE_DIRS})

# link wxWidgets library
target_link_libraries(gui ${wxWidgets_LIBRARIES})

# link curl library
target_link_libraries(gui curl)
target_link_libraries(spotify_api curl)