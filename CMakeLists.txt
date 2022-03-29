cmake_minimum_required(VERSION 3.20)
project(AsteroidGame2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.2.3\\mingw_64\\")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(AsteroidGame2 main.cpp Frame.cpp Frame.h Asteroid.cpp Asteroid.h Player.cpp Player.h Bullet.cpp Bullet.h)
target_link_libraries(AsteroidGame2
        Qt::Core
        Qt::Gui
        Qt::Widgets
        )
