# minesweeper

A simple clone of the classic [Minesweeper](https://en.wikipedia.org/wiki/Minesweeper_(video_game)) game. The code is written in C and uses [SDL2](https://www.libsdl.org) for handling the graphics and mouse input.

Download the latest release here: https://github.com/alfonsojluna/minesweeper/releases

![Windows](/screenshots/windows.png) | ![Linux](/screenshots/linux.png)
:-----------: | :-------------:
Windows | Linux

### How to build on Windows

1. Clone or download this repository
2. [Download](http://tdm-gcc.tdragon.net/download) and install the TDM64-GCC compiler suite. Be sure you check `Add to PATH` during installation.
3. [Download](https://www.libsdl.org/download-2.0.php) the SDL2 development libraries for MinGW and extract them to `minesweeper/libraries/SDL2-2.0.7/...`
4. Compile the program (32-bit):
```
gcc source/minesweeper.c -Ilibraries/SDL2-2.0.7/i686-w64-mingw32/include/SDL2 -Llibraries/SDL2-2.0.7/i686-w64-mingw32/lib -Wall -std=c99 -m32 -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o minesweeper.exe
```
4. Compile the program (64-bit):
```
gcc source/minesweeper.c -Ilibraries/SDL2-2.0.7/x86_64-w64-mingw32/include/SDL2 -Llibraries/SDL2-2.0.7/x86_64-w64-mingw32/lib -Wall -std=c99 -m64 -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o minesweeper.exe
```
5. Copy the SDL2.dll file from `i686-w64-mingw32/bin` (32-bit) or `x86_64-w64-mingw32/bin` (64-bit) to the .exe folder

### How to build on Linux (Ubuntu)

1. Clone this repository: `git clone https://github.com/alfonsojluna/minesweeper`
2. Install SDL2 development libraries: `sudo apt-get install libsdl2-dev`
3. Go to the repository folder: `cd minesweeper`
4. Compile the program:
```
gcc source/minesweeper.c -Wall -std=c99 `sdl2-config --cflags --libs` -o minesweeper
```
5. Run the program: `./minesweeper`
