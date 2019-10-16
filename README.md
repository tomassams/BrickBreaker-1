# BrickBreaker
Exam assignment for course PG4400 C++ programming.

This is our edition of the classic game Arkanoid. Our solution is built using SDL as graphics library and as much as possible of the C\++ standard library. The game at first glance may look simple, but make no mistake. The bricks get harder and harder to break the closer to the top you'll get. Colors display the number of hits you will have to make on one simple brick in order to break it.

<img src="/res/bb1.PNG" width="400"><img src="/res/bb2.PNG" width="400">

## How to run
Open the project in e.g. CLion (Tested on CLion on both Mac and Windows) and hit the run button. The program is extensively tested on both operativsystems. Or you can run the included cmake script yourself.

# How to play BrickBreaker / Controls
- Hit as many bricks as you can, clear the board to win.
- Main Menu: Move up / down with arrow- or W/S keys. Confirm choice with ENTER key
- Ingame: Move sideways with arrow- or A/D keys. Start game with space. Pause/Resume with space. Escape to quit and return to main menu.

## Minimum requirements
- [x] Paddle move backwards and forwards, and stops on the edges of the screen.
- [x] Ball that moves with constant speed and handle bouncing off objects and 
- [x] Ball falls move out of the screen if you let it pass the paddle.
- [x] Bricks on screen that don’t move randomly around.
- [x] Collision detection between ball and brick.
- [x] When all the bricks are gone the game is over.
- [x] The code is runnable.

## Possible extensions
- [x] Bricks have serval lives, and the amount of lives are different for different bricks. This is represented with colors. 
- [x] The game counts points and present it to the user while the game is running.
- [x] We added health to the user. This is represented with harts in the upper right side on the screen.
- [x] We use `std::thread` in order to run the collision checks in parallel. There was however to necessary with any locks.

## What we wish to improve
The paddle has every now and then minor bugs. This causes the ball to act unpredictable and sometimes makes the user loos. This is not fun for any player and we wish we could eradicate this bug.

It would be a lot of fun to add more than one level to the game. Our wish would then be to create levels form input files and the draw different game boards with increased complexity. 

- Henrik Sandberg, Tomas Samset
