cmake_minimum_required(VERSION 3.13)
project(BrickBreaker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${BrickBreaker_SOURCE_DIR}/cmake")

add_executable(BrickBreaker src/main.cpp src/cppfiles/Ball.cpp src/header/Ball.h src/main.cpp src/cppfiles/GameManager.cpp src/header/GameManager.h src/cppfiles/Bricks.cpp src/header/Bricks.h src/header/Brick.h src/cppfiles/InputManager.cpp src/header/InputManager.h src/cppfiles/Paddle.cpp src/header/Paddle.h src/header/GameState.h src/cppfiles/PlayingState.cpp src/header/PlayingState.h src/cppfiles/Renderer.cpp src/header/Renderer.h src/cppfiles/Brick.cpp src/cppfiles/MainMenuState.cpp src/header/MainMenuState.h src/header/InputAction.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(BrickBreaker ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})