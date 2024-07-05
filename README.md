# Math Racer

Math Racer is a physical 2-player arcade game designed to challenge players with mathematical problems in a competitive environment. The game features a dynamic display of problems, interactive inputs, and a real-time scoring system. It uses a combination of hardware components such as LCD screens, potentiometers, buttons, and servos.

## Features

- Randomized math problems (addition, subtraction, multiplication, division)
- Real-time player input
- Competitive scoring system
- Victory and defeat conditions
- Audio feedback for actions and game events

## Components

### Hardware

- LCD screens for displaying problems
- Potentiometers for input
- Buttons for submission and navigation
- Servo motors for physical feedback
- Buzzer for audio feedback

### Software

- Math problem generation and display
- Player input parsing and validation
- Game state management

## Code Overview

### MathGame.cpp

This file contains the core logic for the Math Racer game. The key functionalities include:

- **Generating Math Problems:** Randomly generates math problems involving addition, subtraction, multiplication, and division, and displays them on the LCD screen.
- **Player Input Parsing:** Reads input from potentiometers and buttons to allow players to solve the displayed math problems.
- **Game State Management:** Tracks and updates the game state, including the players' scores, the correctness of answers, and the game's running status.
- **Feedback Mechanisms:** Provides audio feedback using a buzzer for correct and incorrect answers, as well as victory and defeat conditions.
- **Control Mechanisms:** Uses servos to provide physical feedback, indicating the winner of the game.

### Key Functions

- **changeCoord:** Adjusts the cursor position on the LCD screen based on the length of the numbers displayed.
- **displayProblem:** Generates and displays a new math problem on the LCD screen.
- **parseInput:** Parses player inputs and updates the game state based on the correctness of the answers.
- **reset:** Resets the game state for a new game.
- **playDeath:** Plays a "game over" tune using the buzzer.
- **runNextIteration:** Manages the main game loop, updating the state and parsing inputs for each player turn.

---
