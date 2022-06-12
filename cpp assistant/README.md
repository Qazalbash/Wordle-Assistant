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
