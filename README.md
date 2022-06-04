# Wordle-Assistant

[![Watch the video](https://i.pcmag.com/imagery/articles/01O9cD990ECgKwgagoHBoTW-2..v1642710512.png)](test.mp4)

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

Write this command in terminal to compile and run.

```bash
cd "<PATH to directory>" && g++ assistant.cpp -o assistant && "<PATH to directory>/"assistant
```

After this terminal will show a random word from knowlege base like

```
TRY WORD crane
```

Write that word in the wordle and enter the colors,

```
Enter the colors: ybgyy
```

This process will repeat until the moves are over or the word has been guessed.
