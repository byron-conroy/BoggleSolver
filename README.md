# Boggle Solver

## Build Prerequisites

- C++ 17 Compatible Compiler
- CMake Version 3.22 (https://cmake.org/)
- Conan Package Manager Version 1.50 (https://conan.io/)

## Build Steps

Open source directory in terminal window and run the following commands:
1. `mkdir build`
1. `cd build`
1. `cmake ..`
1. `cmake --build .`

## Running the Application

### Windows
Run the following command: `./bin/boggle_game.exe`

### Linux
Run the following command: `./bin/boggle_game`

### Options

| Option              | Description                                   | Optional   |
|---------------------|-----------------------------------------------|------------|
| `--help`            | Prints help                                   | ✅          |
| `--dictionary arg`  | Specify path to dictionary file               | ✅          |
| `--seed arg`        | RNG seed to use when generating the board     | ✅          |
| `--limit arg`       | Time limit for solving the board (in seconds) | ✅          |


