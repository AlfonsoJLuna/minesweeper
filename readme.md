# minesweeper

## Description

Simple [minesweeper](https://en.wikipedia.org/wiki/Minesweeper_(video_game)) clone written in C using [SDL2](https://www.libsdl.org) for the graphics and mouse input.

This is one of the first programs I wrote so don't expect it to be good.

Download the latest release here: https://github.com/alfonsojluna/minesweeper/releases

___

## Screenshots

![Linux](/screenshots/linux.png)

![Windows](/screenshots/windows.png)

___

## How to build on Linux (Ubuntu)

1. Install git: `sudo apt-get install git`
2. Clone this repository: `git clone https://github.com/alfonsojluna/minesweeper`
3. Install SDL2 development libraries: `sudo apt-get install libsdl2-dev`
4. Go to the repository folder: `cd minesweeper`
5. Compile the program:

```
gcc source/minesweeper.c -Wall -std=c99 `sdl2-config --cflags --libs` -o minesweeper
```

6. Run the program: `./minesweeper`

## How to build on Windows

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
