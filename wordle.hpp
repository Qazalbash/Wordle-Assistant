#include <map>
#include <set>
#include <string>
#include <fstream>
#include <iostream>

class Wordle
{
public:
    void game();               // main game
    Wordle(const std::string); // Constructor

private:
    // file object that read/write
    std::ifstream file;
    std::ofstream score;
    // set of all letters that are allowed in the final word
    std::set<char> allowed;
    // the hidden word
    std::string final_word = "*****";
    // map that contains the all the allowed words at each position
    std::map<int, std::set<char>> yes_map;
    // bucket is the word set that we contain after deducing the words from logic
    // big_bucket is all words
    std::set<std::string> bucket = {}, big_bucket = {};

    // true if the game has been won
    bool win = false;
    // stores the size of set of all possible words
    float sample_space_size;
    // starts the game by taking input and sorting them
    void start();
    // reduce the bucket by logic
    void guess_word();
    // read the file and fill the bucket
    void fill_bucket(std::string);
};
