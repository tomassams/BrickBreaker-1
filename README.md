# BrickBreaker
This is our edition of the classic game Arkanoid. Our solution is built using SDL as graphics library and as much as possible of the C\++ standard library. The game at first glance may look simple, but make no mistake. The bricks get harder and harder to break the closer to the top you'll get. Colors display the number of hits you will have to make on one simple brick in order to break it.

## How to run
Open the project in e.g. CLion (Tested on CLion on both Mac and Windows) and hit the run button. The program is extensively tested on both operativsystems. Or you can run the included cmake script yourself.

# How to play BrickBreaker / Controls
- Hit as many bricks as you can, clear the board to win.
- Main Menu: Move up / down with arrow- or W/S keys. Confirm choice with ENTER key
- Ingame: Move sideways with arrow- or A/D keys. Start game with space. Pause/Resume with space. Escape to quit and return to main menu.

## Our process
We started out with some basic code for the game since one of us made the basic structure for the game as his work-assignment. The game is now much more advanced and also a lot more enjoyable. In the beginning of the week we sat down and wrote all the features and improvements we wanted to add to the project. Then we split the work load among us. We used Github heavily to ensure a god flow of code and sharing of progress. 

We sat together everyday during the exam period period (from the morning of 23. to the evening of 25.april) working tirelessly on the code. Our Github will reflect this work quite well. We made a sharable link to our project if you want to take a look please visit https://cantinur.github.io/BrickBreaker/

## Pair programming 
At the end of 25 of April we sat together on one computer and did pair programming. This is the act where one of us was the driver (person writing code) and the other was an observer (reading trough every new line of code and commenting out loud if it needed to be changed). We did this to complete some last parts of our project that we wanted to do before we turned in the project.  

## Choices we made
We decided quite early that we needed to split up different areas of the code in order to easier handle different aspects of the program. For one, we just needed to make one SDL Window so to handle that and to handle only one renderer we made classes. The advantage we got was to give the classes specific arias to handle. This ensured  a cleaner codebase and something that would be more scalable if we wanted to expand our program in the future.  

We did the same with all the game logic elements. We have a collision detection class that only has two external methods `collision` and `brickCollisions` that returns the amount of brick hits. 

### Use of virtual
We decided to structure the game in game states, and cycle the game loop according to the current state the game was in. We made gamestate a virtual class as an interface and made state classes that implemented this functionality. This also would set us up for extending the game with more gamestates handily.

### Use of standard library
One of the many features of our game is the use of the standard library. We use `std::vectors` in stead of arrays and other collections, and we use `std::for_each` where it was the better choice. Our thread management was by using `std::thread` and even out random number is accessed trough `std::random_device`,  `std:: default_random_engine` and the `std::uniform_int_distribution`. The quality of the functions from the standard library is in all likelihood better than other third party libraries we might end up using. 

### Smart pointers
We used smart pointers to handle our gamestate as well as to handle our renderer state. This is used for the renderer. Smart pointers acts as a wrapper for other pointers in order to handle the lifetime to the object being pointed too. The gamestate was handled with `std::unique_ptr` to make sure it disposes of the pointer automatically when it goes out of scope. The renderer was kept in a shared pointer which then allowed usage of the renderer class from all gamestates without having to reinitialize. 

## What we like about our project
This was a fun experience for us. Creating a game was a lot of fun and made us think differently to a lot of problems. We think we have made a solid game and shown in the proses a relatively good understanding for CPP. The code is concise and quite readable. 

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