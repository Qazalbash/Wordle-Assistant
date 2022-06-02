#include "wordle.hpp"

Wordle::Wordle(std::string fn)
{
    fill_bucket(fn);
}

void Wordle::fill_bucket(std::string filename)
{
    file.open(filename);
    std::string w;
    while (file)
    {
        file >> w;
        bucket.insert(w);
    }
    default_bucket = bucket;
}

void Wordle::game()
{
    for (int i = 0; i < 5; i++)
    {
        if (final_word.find('*') == std::string::npos)
        {
            std::cout << std::endl
                      << std::endl
                      << "############################################################" << std::endl
                      << "There is high probablity to win this Wordle with word: " << final_word << std::endl
                      << "############################################################" << std::endl;
            break;
        }
        else
        {
            start();
        }
    }
}

template <class T>
void input(std::string message, T &var)
{
    std::cout << std::endl
              << message;
    std::cin >> var;
    std::cout << std::endl;
}

template <class T>
void print(std::string message, std::set<T> set)
{
    std::cout << message;
    for (auto set_iter = set.begin(); set_iter != set.end(); ++set_iter)
    {
        std::cout << *set_iter << "\t";
    }
    std::cout << std::endl;
}

void Wordle::start()
{
    std::string input_word, result;
    std::cout << "------------------------------------"
              << "------------------------------------"
              << "------------------------------------"
              << "------------------------------------" << std::endl;

    do
    {
        input("Enter the word: ", input_word);
    } while (warning("Word should be of length", input_word, 5) ||
             default_bucket.find(input_word) == default_bucket.end());

    do
    {
        input("Enter the result: ", result);
    } while (warning("Word should be of length", result, 5));

    for (int i = 0; i < 5; i++)
    {
        if (result[i] == 'G' || result[i] == 'g')
        {
            if (final_word[i] == '*')
            {
                final_word[i] = input_word[i];

                for (int j = 97; j < 123; j++)
                {
                    if (j != (int)input_word[i])
                    {
                        no_map[i].insert((char)j);
                    }
                }

                yellow.insert(input_word[i]);
            }
        }

        else if (result[i] == 'Y' || result[i] == 'y')
        {
            no_map[i].insert(input_word[i]);
            yellow.insert(input_word[i]);
        }

        else if (result[i] != 'B' && result[i] != 'b' &&
                 result[i] != 'W' && result[i] != 'w')
        {
            std::cout << "The input is wrong" << std::endl;
            start();
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (result[i] == 'B' || result[i] == 'b' ||
            result[i] == 'W' || result[i] == 'w')
        {
            if (yellow.find(input_word[i]) == yellow.end() ||
                final_word.find(input_word[i]) == std::string::npos)
            {
                for (int j = 0; j < 5; j++)
                {
                    no_map[j].insert(input_word[i]);
                }
            }
        }
    }

    std::cout << std::endl
              << std::endl
              << "Word is becoming = " << final_word << std::endl
              << std::endl
              << std::endl;

    guess_word(input_word);
}

void Wordle::guess_word(std::string word)
{
    int index;
    std::set<std::string> demo = bucket;

    for (std::map<int, std::set<char>>::iterator it = no_map.begin();
         it != no_map.end(); ++it)
    {
        index = (*it).first;

        for (std::set<char>::iterator it2 = (*it).second.begin();
             it2 != (*it).second.end(); ++it2)
        {
            for (std::set<std::string>::iterator it3 = bucket.begin();
                 it3 != bucket.end(); ++it3)
            {
                if ((*it3)[index] == *it2)
                {
                    demo.erase(*it3);
                }
            }
        }
    }

    bucket = demo;

    for (std::set<std::string>::iterator it = bucket.begin();
         it != bucket.end(); ++it)
    {
        for (std::set<char>::iterator it2 = yellow.begin();
             it2 != yellow.end(); ++it2)
        {
            if ((*it).find(*it2) == std::string::npos)
            {
                demo.erase(*it);
            }
        }
    }

    bucket = demo;

    print("possible words = ", bucket);
    // print("Yellows: ", yellow);

    if (bucket.size() == 1)
    {
        final_word = *bucket.begin();
    }
}

bool Wordle::warning(std::string message, std::string var, const int size)
{
    if (var.size() != size)
    {
        std::cout << message << " " << size << std::endl;
        return true;
    }
    return false;
}
