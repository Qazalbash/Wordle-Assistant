#include <ctime>
#include "wordle.hpp"

Wordle::Wordle(std::string fn)
{
    fill_bucket(fn);
}

void Wordle::fill_bucket(std::string filename)
{
    std::string w;
    file.open(filename);

    while (file)
    {
        file >> w;            // reading the words line by line
        big_bucket.insert(w); // inserting into bucket
    }

    file.close();
}

void Wordle::game()
{
    bucket = big_bucket;
    /*
    at start all 26 letters are equally likely at all
    positions so adding them in the yes_map
    */
    for (int i = 0; i < 5; i++)
    {
        for (int j = 97; j < 123; j++)
        {
            yes_map[i].insert((char)j);
        }
    }

    score.open("score.txt", std::ios::app);

    for (int i = 0; i < 6; i++)
    {
        start();
    }

    if (win)
    {
        score << "\nwin\n";
    }
    else
    {
        score << "\nlose\n";
    }

    score.close();
}

template <class T>
void input(const std::string &message, T &var)
{
    std::cout << std::endl
              << message;
    std::cin >> var;
    std::cout << std::endl;
}

bool warning(const std::string &message,
             const std::string &var,
             const int size)
{
    if (var.size() == size)
    {
        return false;
    }
    std::cout << message << " " << size << std::endl;
    return true;
}

bool color_check(std::string colors)
// checks if all colors are valid
{
    bool again = false;
    std::set<char> color = {'B', 'Y', 'G', 'W', 'b', 'y', 'g', 'w'};
    for (int i = 0; i < 5; i++)
    {
        again = again && (color.find(colors[i]) != color.end());
    }
    return again;
}

void Wordle::start()
{
    srand(time(0));
    std::string guessed_word, result;
    sample_space_size = bucket.size();

    if (win)
    {
        score << 1 << " ";
    }
    else if (sample_space_size > 0)
    {
        // randomly selects a word from set of all equally likely words
        guessed_word = *std::next(bucket.begin(), rand() % bucket.size());

        std::cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << std::endl
                  << std::endl
                  << "Probability of being correct " << 1 / sample_space_size << std::endl
                  << std::endl
                  << "TRY WORD " << guessed_word << std::endl;

        do
        {
            input("Enter the colors: ", result);
        } while (warning("Word should be of length", result, 5) || color_check(result));

        // sroting the input word to the respective places in accordance to result
        for (int i = 0; i < 5; i++)
        {
            if (result[i] == 'G' || result[i] == 'g')
            {
                if (final_word[i] == '*')
                {
                    final_word[i] = guessed_word[i];

                    yes_map[i] = {guessed_word[i]};

                    allowed.insert(guessed_word[i]);
                }
            }

            else if (result[i] == 'Y' || result[i] == 'y')
            {
                yes_map[i].erase(guessed_word[i]);
                allowed.insert(guessed_word[i]);
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (result[i] == 'B' || result[i] == 'b' ||
                result[i] == 'W' || result[i] == 'w')
            {
                if (allowed.find(guessed_word[i]) == allowed.end())
                {
                    for (int j = 0; j < 5; j++)
                    {
                        yes_map[j].erase(guessed_word[i]);
                    }
                }
                else
                {
                    yes_map[i].erase(guessed_word[i]);
                }
            }
        }

        std::cout << "Word is becoming = " << final_word << std::endl
                  << std::endl;

        // guessing the words
        guess_word();

        score << sample_space_size << " ";
        win = result == "ggggg";
    }

    else if (sample_space_size == 0)
    {
        win = false;
        std::cout << "No more option left" << std::endl;
    }
}

void Wordle::guess_word()
{
    std::set<std::string> demo = {};

    // filter only those words, whose each letter is allowed by yes_map at that place
    for (std::map<int, std::set<char>>::iterator nm = yes_map.begin();
         nm != yes_map.end(); ++nm)
    {
        for (std::set<std::string>::iterator b = bucket.begin();
             b != bucket.end(); ++b)
        {
            if (((*nm).second).find((*b)[(*nm).first]) == ((*nm).second).end())
            {
                demo.insert(*b);
            }
        }
    }

    // filter those words which contain all the allowed words
    for (std::set<std::string>::iterator b = bucket.begin();
         b != bucket.end(); ++b)
    {
        for (std::set<char>::iterator a = allowed.begin();
             a != allowed.end(); ++a)
        {
            if ((*b).find(*a) == std::string::npos)
            {
                demo.insert(*b);
            }
        }
    }

    for (std::set<std::string>::iterator it = demo.begin();
         it != demo.end(); ++it)
    {
        bucket.erase(*it);
    }

    sample_space_size = bucket.size();
}
