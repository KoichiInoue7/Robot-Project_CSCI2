# Robot Arena Game (C++)

A turn-based console game: the player is trapped in a grid arena with robots and has
to destroy them all before one of them catches up.

Built for CSCI 2 at El Camino College. My professor provided the skeleton and the test
driver. I implemented the methods of the `Arena`, `Player`, `Robot` and `Game` classes.

## How the game works

- The arena is a grid (up to 20 × 40) with one player `@` and up to 130 robots `R`.
  A square with several robots shows the count instead (`2`–`9`).
- Each turn the player can:
  - **move** up / down / left / right
  - **stand** still
  - **shoot** in a direction (range of 5 squares, hits the first robot in line)
  - let the **computer choose** a move
- After the player's turn, every robot moves one square in a random direction.
- A robot is destroyed after **two hits**.
- If a robot moves onto the player's square, the player dies.
- The player wins by destroying every robot.

## Design

| class | responsibility |
|---|---|
| `Game` | sets up the arena and runs the turn loop |
| `Arena` | the grid: owns the player and robots (`new` / `delete`), moves robots, displays the board |
| `Player` | position, moving, shooting, the computer-chosen turn |
| `Robot` | position, random movement, taking damage |

Each class has its own `.h` / `.cpp` file. Forward declarations (`class Arena;`) are
used so classes that refer to each other don't create circular `#include`s.

## Build and run

```bash
g++ -std=c++17 Project3NEw/Project3/*.cpp -o robots
./robots
```

Or open `Project3NEw/Project3/Project3.sln` in Visual Studio.

`main.cpp` is the course's test driver: enter a test number (1–35) and it checks one
behaviour of the classes, printing `Passed` if it works.

## What I learned

- Splitting a program into multiple classes and files, and how `#include` and forward
  declarations fit together
- Managing objects created with `new`: the arena owns its robots and must `delete`
  each one when it's destroyed or when the arena goes away
