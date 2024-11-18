# TicTacToe CLI

This repository is a demonstration project showcasing how a modern C++ project could be built in a way that's production ready.
The main branch currently contains a working but totally unsafe program that is ready to test for yourself.

The production branch is always subject to futher changes and testing, but it is a huge improvement over the sample code in the main branch.

## The Production Branch

This branch incorporates C++ best practices as much as possible. It uses the following solutions for the vulnerabilites listed in the main branch:

- ANSI escape codes rather than calling system().
- Includes compiler hardening flags.
- Uses std::strtol() for more proper error handling of string inputs. (This could be simplified even futher, but it works for our use case.)
- Uses std::span on user provided arguments to eliminate dangerous pointer arithmitic.
  - Indexing the board is done on a fix-sized string, and the indicies clamped to a hard-coded range. After fuzz testing with ASAN enabled, this approach seems ok for our use case.

This branch also incorporates a fuzz testing library to check that the game logic sanitizes all user inputs properly. I currently don't have a test for checking comand arguments.
