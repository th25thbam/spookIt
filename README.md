# spookIt (Pumpkin Pop)
> pop spooky pumpkins and score points before they pop themself

## Description 
A Clean, interactive C++ game built from scratch using Raylib Library. Players test their reflexes by clicking on spooky pumpkins that spawn dynamically in time. The game features progressive difficulty, animations, and a night sky aesthetic that is based on a dark and spooky theme.

## Preview
![preview](image.png)
![preview](image-1.png)

## Features 
**Modular Architecture:** Cleanly organized codebase separating game mechanics.

**Responsive Display:** The game automatically scales to fit any window size or full screen mode.

**Progressive Difficulty:** The game speeds up the longer the player survives.

**Aesthetic Visuals:** Custom Visuals defined to match the dark and spooky theme.

## Technologies & Tools
Language: C++<br>
Library: Raylib<br>
Build System: GNU Make (Makefile)

## How to play spookIt
Before building spookIt, ensure you have C/C++ compiler and Raylib library installed [https://github.com/raysan5/raylib]

### Linux & WSL(Ubuntu/Debian)

1. **Clone the repository:**
   ```bash
   git clone https://github.com/th25thbam/spookIt
   cd spookIt

2. Install Raylib dependencies:
    ```base
    sudo apt update
    sudo apt install build-essential libraylib-dev libgl1-mesa-dev libopenal-dev

3. Compile and run using Makefile
    ```bash
    make run
4. Prebuilt binary files are available in the releases tab for debian based linux distributions

### Windows(MinGW/MSYS2)
1. Clone Repository
2. Install Raylib and GCC using MYSY2:
    ```bash
    pacman -S mingw-w64-ucrt-x86_64-raylib mingw-w64-ucrt-x86_64-gcc
3. Compile manually using g++
    ```bash
    g++ main.cpp functions.cpp globals.cpp -o spookIt.exe -lraylib -lopengl32 -lgdi32 -lwinmm

### macOS(Homebrew)
1. Clone Repository
2. Install Raylib
    ```bash
    brew install rayib
3. Compile manually using g++
    ```bash
    g++ main.cpp functions.cpp globals.cpp -o spookIt -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

#### Game controls
    - press space to start playing.
    - mouse left click to pop pumpkins.
    - press R to restart after all lives have been consumed.
    - press Esc to exit.

## Inspiration
i wanted to try making an aim trainer in 2D while keeping it simple and fun, and using visuals that would match the dark and spooky halloween theme of october.


