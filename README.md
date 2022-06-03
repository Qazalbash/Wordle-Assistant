# Wordle-Assistant

## Description

[Wordle](https://www.nytimes.com/games/wordle/index.html) is a popular game developed by [New York Times](https://www.nytimes.com/).

## How to play

Guess the WORDLE in six tries.

Each guess must be a valid five-letter word. Hit the enter button to submit.

After each guess, the color of the tiles will change to show how close your guess was to the word.

### Example

🟢⚪⚪⚪⚪

The letter 🟢 is in the word and in the correct spot.

⚪🟡⚪⚪⚪

The letter 🟡 is in the word but in the wrong spot.

⚪⚪⚫⚪⚪

The letter ⚫ is not in the word in any spot.

## Requirments

The requirments are `C++` fully functional. `gcc` compiler.

## How to run

Run the `assitant.cpp` and it will ask from input. Enter the guessed words and the colors (in order), terminal will show the set of all possible words that make you win this game. The possible words are sorted in alphabetical order.
