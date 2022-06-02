#include "wordle.hpp"

Wordle::Wordle(std::string fn) : filename(fn)
{
    fill_bucket();
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

void Wordle::fill_bucket()
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

void Wordle::guess_word(std::string word)
{
    bool keep;
    std::set<std::string> demo;
    std::string matched_word;

    demo = bucket;

    for (std::set<std::string>::iterator bucket_item = bucket.begin();
         bucket_item != bucket.end(); ++bucket_item)
    /*
    removing all the elements that contain any of the black letter
    or does not contain any yellow letter
    */
    {
        matched_word = *bucket_item;
        keep = true;
        for (std::set<char>::iterator black_it = not_allowed.begin();
             black_it != not_allowed.end(); ++black_it)
        {
            if (matched_word.find(*black_it) != std::string::npos)
            {
                demo.erase(matched_word);
                break;
            }
        }

        for (std::set<char>::iterator yellow_it = allowed.begin();
             yellow_it != allowed.end(); ++yellow_it)
        {
            if (matched_word.find(*yellow_it) == std::string::npos)
            {
                demo.erase(matched_word);
                break;
            }
        }
    }

    bucket = demo;

    for (std::set<std::string>::iterator match_it = bucket.begin();
         match_it != bucket.end(); ++match_it)
    // passing only those elements which have same green elements
    {
        keep = true;
        matched_word = *match_it;
        for (int i = 0; i < 5; i++)
        {
            if (final_word[i] != '*' && matched_word[i] != final_word[i])
            {
                demo.erase(matched_word);
                break;
            }
        }
    }

    bucket = demo;

    print("possible words = ", bucket);

    if (bucket.size() == 1)
    {
        final_word = *bucket.begin();
    }
}

template <class T>
void Wordle::input(std::string message, T &var)
{
    std::cout << std::endl
              << message;
    std::cin >> var;
    std::cout << std::endl;
}

inline bool Wordle::warning(std::string message, std::string var, const int size)
{
    if (var.size() != size)
    {
        std::cout << message << " " << size << std::endl;
        return true;
    }
    return false;
}

void Wordle::start()
{
    std::string input_word, result;
    std::cout << "-------------------------------------------------------"
              << "-------------------------------------------------------"
              << "-------------------------------------------------------"
              << "-------------------------------------------------------" << std::endl;

    do
    {
        input("Enter the word: ", input_word);
    } while (warning("Word should be of length", input_word, 5));

    if (default_bucket.find(input_word) == default_bucket.end())
    {
        std::cout << "Word is not in the list" << std::endl;
    }

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
                // yellow.erase(input_word[i]);
            }
        }
        else if (result[i] == 'Y' || result[i] == 'y')
        {
            allowed.insert(input_word[i]);
        }
        else if (result[i] == 'B' || result[i] == 'b' ||
                 result[i] == 'W' || result[i] == 'w')
        {
            if (allowed.find(input_word[i]) == allowed.end())
            {
                not_allowed.insert(input_word[i]);
            }
        }
        else
        {
            std::cout << "The input is wrong" << std::endl;
            start();
        }
    }

    std::cout << std::endl
              << std::endl
              << "Word is becoming = " << final_word << std::endl
              << std::endl
              << std::endl;

    // for (std::set<char>::iterator it = allowed.begin();
    //      it != allowed.end(); ++it)
    // {
    //     if (not_allowed.find(*it) != not_allowed.end())
    //     {
    //         not_allowed.erase(*it);
    //     }
    // }

    // for (std::string::iterator i = final_word.begin(); i != final_word.end(); ++i)
    // {
    //     if (*i != '*' && not_allowed.find(*i) != not_allowed.end())
    //     {
    //         not_allowed.erase(*i);
    //     }
    // }

    // print("Letters     in the word = ", allowed);
    // print("Letters not in the word = ", not_allowed);

    guess_word(input_word);
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