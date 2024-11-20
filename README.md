# TicTacToe CLI

This repository is a demonstration project showcasing how a modern C++ project could be built in a way that's production ready.
The main branch currently contains a working but totally unsafe program that is ready to test for yourself.

The production branch is always subject to futher changes and testing, but it is a huge improvement over the sample code in the main branch.

## Overview

This branch incorporates C++ best practices as much as possible. It uses the following solutions for the vulnerabilites listed in the main branch:

- ANSI escape codes rather than calling system().
- Includes compiler hardening flags.
- Uses std::strtol() for more proper error handling of string inputs. (This could be simplified even futher, but it works for our use case.)
- Uses std::span on user provided arguments to eliminate dangerous pointer arithmitic.
  - Indexing the board is done on a fix-sized string, and the indicies clamped to a hard-coded range. After fuzz testing with ASAN enabled, this approach seems ok for our use case.

This branch also incorporates a fuzz testing library to check that the game logic sanitizes all user inputs properly. I currently don't have a test for checking comand arguments.

## Setup Instructions

Everything is pretty self contained, requiring only a basic CMake setup. It should work with little effort on Windows and Linux. I am unable to test this on a macOS.

### Dependencies

- CMake version 3.25 or later.
- A recent version of Ninja.
- A Compiler that supports C++20. The 3 big ones are supported out of the box:
  - MSVC
  - LLVM
  - GCC
- Optional dependencies.
  - A Linux-based operating system is required to run the fuzz test.
  - ccache
  - clang-tidy
  - cppcheck

### Configure and Build

The project comes with default presets for Debug mode and Release mode. Both of these use *Ninja* and *Clang* by default.
In the root directory of the project, enter the following command for a simple configutation:

`cmake . --preset=<your preset> [other variables are optional]`

The following variables are available that you can set if you need to:

- These can be set if that respective tool is not in your system include path or is aliased.
  - CLANG_TIDY_EXE
  - CPPCHECK_EXE
  - CCACHE_EXE
- Set this to ON to enable fuzz testing.
  - TICTACTOE_FUZZING

The final step is to build and run your project using the following commands.

`cmake --build ./build/<your preset>/`

`cd ./build/<your preset>/tictactoe_cli`

`./tictactoe_cli [optional arguments]`

Then enjoy the game!

## Arguments

The game supports the following arguments:

- `--player1 <player name>`
- `--player2 <player name>`

## Fuzz Testing

For those who are curious, you can build this project with fuzz testing as described above. The executable will appear in your `build/<your preset>` directory.
