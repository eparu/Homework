#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <string>


//constexpr std::size_t SIZE = 1000000;

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

template < typename T >
void hash_combine(std::size_t& seed, const T& value) noexcept
{
    seed ^= std::hash < T >()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept
{
    hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types& ... args) noexcept
{
    hash_combine(seed, value);
    hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types& ... args) noexcept
{
    std::size_t seed = 0;
    hash_value(seed, args...);
    return seed;
}




int main(int argc, const char * argv[]) {
    for (std::size_t SIZE = 100000; SIZE <= 1000000; SIZE += 100000)
    {
        std::set < std::size_t > hash;
        unsigned int counter_collisions = 0;

        std::set < std::string > strings = make_random_words(SIZE);
        std::vector < int > numbers(SIZE);
        for (auto& i :numbers)
        {
            i = rand();
        }

        auto i = 0U;
        for (const auto & str : strings)
        {
            if (!(hash.insert(hash_value(str, numbers[i++])).second))
            {
                counter_collisions++;
            }
        }

        std::cout << std::left << std::setw(9) << SIZE << std::setw(5) << counter_collisions << std::endl;
    }

    return 0;
}
