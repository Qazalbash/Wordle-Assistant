#include "wordle.cpp"

int main()
{
    // data set was obatined from github repository of Grand Sanderson
    Wordle w = {"allowed_words.txt"};
    // starting the game
    w.game();
    return 0;
}

/*
Just a thought why wouldn't I enter the hidden word and
simulate the game for that word.
*/