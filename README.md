# SnakeGame

A little C++ project, the classic [snake](https://en.wikipedia.org/wiki/Snake_(video_game_genre)) game. Mostly as an exploration of C++ fundamentals, object oriented design, working with external libraries, and making games. Written in the C++17 standard, using SFML 3.0.0, in Visual Studio, for 64-bit Windows systems.

To run the game, download the zip file [here](https://github.com/Venerance/SnakeGameUsingSFML/releases/download/v1.0/SnakeGame.zip), extract it, run Snek.exe and enjoy.

Any additional suggestions, feedback and critique regarding the program and the overall design is appreciated.

***

# High level overview of the program

**Utils.hpp**
:   Fairly small, just contains functions to pack two 16-bit integers into a 32-bit integer and to undo the process. Implemented since the standard library unordered_map container does not have a default hash for a pair of integers.

**Food.hpp**
:   Handles the generation of the food object that serves to grow the snake, uses the standard library mt19937 class (based on the Mersenne Twister algorithm) to generate the random numbers for the food coordinates.

**Snake.hpp**
:   Handles the snake entity in general, includes the Direction system. Moving the snake and validating the turning input are its two primary methods.

**Board.hpp**
:   Handles the overall state of the board, it is basically the primary class for the game. Processing the input, updating the game state (including Paused and Game Over states), and rendering the game are its primary methods. 

**main.cpp**
:   Where the main game loop runs, creates the window, specifies the frame rate, and calls the relevant Board class methods as needed within the game loop.

***

# Possible improvements

- Using a CMake template to avoid having to include the SFML library within the repository itself while still avoiding absolute system paths.
- Using a separate file to store high scores across different play sessions.
- Inelegant use of the SFML text class in Board.hpp, while it works, it also seems hard to scale up or modify.
- Better distribution of duties among the header files, I prioritized splitting tasks according to what "feels" right for a class to do. Might have added unnecessary complexity in the process.
- The game currently is only built for Window x64 systems, could work on allowing it to run on different systems.
- Polishing the game, more dynamic screen sizing, speed changing over time perhaps.

***

# Credits

**Third-Party Libraries**

This project uses [SFML](https://github.com/SFML/SFML) 
Copyright © Laurent Gomila - licensed under the zlib license.
The SFML license is included in `external/SFML/LICENSE.md` [link](external/SFML/LICENSE.md)

**Fonts**

The font used for the in-game text objects is [PixelLetters](https://www.fontspace.com/pixelletters-font-f22954) by GeelynEdits on fontspace

***

# License

This project is open-source (MIT License), see [LICENSE](LICENSE.txt) for details
