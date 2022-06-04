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
        file >> w;        // reading the words line by line
        bucket.insert(w); // inserting into bucket
    }

    big_bucket = bucket;
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
}

void Wordle::game()
{
    for (int i = 0; i < 6; i++)
    {
        // if there is no * in our final_word then it is the answer
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
    for (auto set_iter = set.begin();
         set_iter != set.end(); ++set_iter)
    {
        std::cout << *set_iter << "\t";
    }
    std::cout << std::endl;
}

bool warning(std::string message, std::string var, const int size)
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
    srand(time(0));
    std::string guessed_word, result;
    if (bucket.size())
    {
        guessed_word = *std::next(bucket.begin(), rand() % bucket.size());
    }
    else
    {
        std::cout << "No more option left" << std::endl;
    }

    std::cout << std::endl
              << "TRY WORD " << guessed_word << std::endl;

    do
    {
        input("Enter the colors: ", result);
    } while (warning("Word should be of length", result, 5));

    if (
        result.find('B') != std::string::npos && result.find('b') != std::string::npos &&
        result.find('Y') != std::string::npos && result.find('y') != std::string::npos &&
        result.find('G') != std::string::npos && result.find('g') != std::string::npos &&
        result.find('W') != std::string::npos && result.find('w') != std::string::npos)
    {
        std::cout << "The input is wrong" << std::endl;
        start();
    }

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
}

void Wordle::guess_word()
{
    std::set<std::string> demo = bucket;

    // filter only those words, whose each letter is allowed by yes_map at that place
    for (std::map<int, std::set<char>>::iterator nm = yes_map.begin();
         nm != yes_map.end(); ++nm)
    {
        for (std::set<std::string>::iterator b = bucket.begin();
             b != bucket.end(); ++b)
        {
            if (((*nm).second).find((*b)[(*nm).first]) == ((*nm).second).end())
            {
                demo.erase(*b);
            }
        }
    }

    bucket = demo;

    // filter those words which contain all the allowed words
    for (std::set<std::string>::iterator b = bucket.begin();
         b != bucket.end(); ++b)
    {
        for (std::set<char>::iterator a = allowed.begin();
             a != allowed.end(); ++a)
        {
            if ((*b).find(*a) == std::string::npos)
            {
                demo.erase(*b);
            }
        }
    }

    bucket = demo;
    // print all the possible words from dataset
    print("possible words = ", bucket);
}
