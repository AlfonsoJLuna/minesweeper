# Minesweeper

*A clone of the classic Minesweeper game.*

This is one of the first programs I wrote. The code is written in C and uses SDL2 for handling the graphics and the mouse input. The game has been tested to run on both Windows and Linux.

A compiled release is available here: https://github.com/AlfonsoJLuna/minesweeper/releases

![](/screenshots/minesweeper-1.jpg) | ![](/screenshots/minesweeper-2.jpg)
:---------------------------------: | :---------------------------------:

## Building instructions

### How to build on Linux

1. Clone this repository:
```
git clone https://github.com/AlfonsoJLuna/minesweeper
```
2. Install SDL2 development libraries. For example, on Ubuntu:
```
sudo apt-get install libsdl2-dev
```
3. Go to the repository folder:
```
cd minesweeper
```
4. Compile the program:
```
gcc source/minesweeper.c -Wall -std=c99 `sdl2-config --cflags --libs` -o minesweeper
```
5. Run the program:
```
./minesweeper
```

### How to build on Windows

1. Clone or download this repository.
2. Download and install the mingw-w64 toolchain. Prebuilt binaries are available [here](https://gnutoolchains.com/mingw64/). Be sure you check `Add to PATH` during installation.
3. [Download](https://www.libsdl.org/release/SDL2-devel-2.0.12-mingw.tar.gz) the SDL2 development libraries for MinGW and extract them to `minesweeper/libraries/SDL2-2.0.12/...`
4. Open a command prompt and go to the repository folder.
5. Compile the program:
```
gcc source/minesweeper.c -Ilibraries/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2 -Llibraries/SDL2-2.0.12/x86_64-w64-mingw32/lib -Wall -std=c99 -m64 -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -o minesweeper.exe
```
6. Copy the `SDL2.dll` file from `minesweeper/libraries/SDL2-2.0.12/x86_64-w64-mingw32/bin/` to `minesweeper/`.
7. Run the program: `minesweeper.exe`
