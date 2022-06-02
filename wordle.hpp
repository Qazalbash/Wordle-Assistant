#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Wordle
{
public:
    void game();
    Wordle(const std::string);

private:
    std::ifstream file;
    std::set<char> yellow;
    std::map<int, std::set<char>> no_map;
    std::string final_word = "*****";
    std::set<std::string> bucket = {}, default_bucket = {};

    void start();
    void guess_word(std::string);
    void fill_bucket(std::string);

    bool warning(std::string, std::string, const int);
};