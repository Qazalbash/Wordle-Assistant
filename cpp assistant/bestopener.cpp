#include <map>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

int main()
{
    std::string w;
    std::ifstream file;
    std::map<int, int> count;
    std::set<std::string> bucket;

    file.open("allowed_words.txt");

    while (file)
    {
        file >> w;        // reading the words line by line
        bucket.insert(w); // inserting into bucket
    }

    file.close();

    for (int i = 97; i < 123; i++)
    {
        count.insert(std::pair<int, int>{i, 0});
    }

    for (std::set<std::string>::iterator word = bucket.begin(); word != bucket.end(); ++word)
    {
        for (int i = 0; i < 5; i++)
        {
            count[(int)((*word)[i])] = count[(int)((*word)[i])] + 1;
        }
    }
    std::cout << "[" << std::endl;
    for (std::map<int, int>::iterator j = count.begin(); j != count.end(); ++j)
    {
        std::cout << "(\"" << (char)(j->first) << "\" , " << j->second << "),";
    }
    std::cout << "]" << std::endl;

    /*
    The letters and their count sorted in decending order are given below.

        ('e', 6656),
        ('s', 6650),
        ('a', 5987),
        ('o', 4429),
        ('r', 4156),
        ('i', 3753),
        ('l', 3369),
        ('t', 3292),
        ('n', 2950),
        ('u', 2509),
        ('d', 2448),
        ('y', 2067),
        ('c', 2023),
        ('p', 2015),
        ('m', 1975),
        ('h', 1756),
        ('g', 1640),
        ('b', 1625),
        ('k', 1495),
        ('f', 1113),
        ('w', 1038),
        ('v', 694),
        ('z', 434),
        ('j', 291),
        ('x', 288),
        ('q', 112)

    If we take top 5 letters which are 'e', 's', 'a', 'o', 'r', and search a
    word in the the list that contain all the letters, then that word turn out
    to be 'soare'.
*/

    return 0;
}
