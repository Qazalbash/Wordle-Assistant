#include "wordle.cpp"

int main()
{
    Wordle w = {"allowed_words.txt"};
    w.game();
    return 0;
}