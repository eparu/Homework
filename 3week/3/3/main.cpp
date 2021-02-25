#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include <boost/functional/hash.hpp>

constexpr std::size_t SIZE = 10;

std::set < std::string > make_random_words(std::size_t N, std::size_t length = 10)
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast < std::size_t > (std::chrono::system_clock::now().time_since_epoch().count()));
    std::set < std::string > words;

    for (std::string s(length, '_'); words.size() < N; words.insert(s))
    {
        for (auto & c : s)
            c = letter(e);
    }

    return words;
}


int main(int argc, const char * argv[]) {
    std::set < std::size_t > hash_string;
    std::set < std::size_t > hash_int;
    unsigned int counter_collisions_strings = 0;
    unsigned int counter_collisions_int = 0;


    std::set < std::string > strings = make_random_words(SIZE);
    std::set < int > numbers;

    while (numbers.size() < SIZE)
    {
        numbers.insert(rand());
    }

    for (const auto& i : strings)
    {
        auto added = (hash_string.insert(boost::hash_value(i))).second;
        if (!added) counter_collisions_strings++;
    }

    for (const auto& i : numbers)
    {
        auto added = (hash_string.insert(boost::hash_value(i))).second;
        if (!added) counter_collisions_int++;
    }


    std::cout << counter_collisions_strings << std::endl;

    std::cout << counter_collisions_int << std::endl;

    return 0;
}
