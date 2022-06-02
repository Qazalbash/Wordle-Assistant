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
    std::set<char> allowed, not_allowed;
    std::map<int, std::set<int>> no_map;
    std::string filename, final_word = "*****";
    std::set<std::string> bucket = {}, default_bucket = {};

    void start();
    void fill_bucket();
    void guess_word(std::string);

    template <class T>
    void input(std::string, T &);

    inline bool warning(std::string, std::string, const int);
};