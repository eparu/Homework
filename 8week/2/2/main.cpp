#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <map>


std::string make_sequence(std::size_t N)
{
    std::uniform_int_distribution <> uid(0, 3);
    std::default_random_engine dre(42);
    std::map<std::size_t, char> number_into_letter;
    number_into_letter[0] = 'A';
    number_into_letter[1] = 'G';
    number_into_letter[2] = 'T';
    number_into_letter[3] = 'C';

    std::string result(N, '-');
    for (auto & c: result)
    {
        c = number_into_letter[uid(dre)];
    }
    return result;
}


template<typename T>
void safe_push_back(std::vector<T>& vector, T value, std::mutex& mutex)
{
    std::scoped_lock lock(mutex);
    vector.push_back(value);
}


struct searchSubstr
{
    void operator()(const std::string & substr, const std::string & str,
                    std::size_t first, std::size_t last, std::vector<std::size_t>& indices, std::mutex& mutex)
    {
        auto begin = std::begin(str);

        for (auto index = first; index < last; ++index)
        {
            auto it1 = std::begin(substr);
            auto it2 = std::next(begin, index);
            for (; it1 != std::end(substr) && *it1 == *it2; ++it1, ++it2);
            if (it1 == std::end(substr))
            {
                safe_push_back(indices, index, mutex);
            }
        }
    }
};


void parallelSearch(const std::string& substr, const std::string& str, std::size_t first_index, std::size_t last_index, std::vector<std::size_t>& indices, std::mutex& mutex)
{
    const std::size_t hardware_threads = std::thread::hardware_concurrency();
    const unsigned int block_size =(str.size() - substr.size() + 1) /hardware_threads;

    if ((last_index - first_index) <= std::max(4U,  block_size))
    {
        searchSubstr()(substr, str, first_index, last_index, indices, mutex);
    }
    else
    {
        auto middle_index = first_index + (last_index - first_index) / 2;

        std::future < void > first_half = std::async(parallelSearch, std::cref(substr), std::cref(str), first_index, middle_index, std::ref(indices), std::ref(mutex));

        parallelSearch(substr, str, middle_index, last_index, indices, mutex);

        first_half.get();
    }
}

void parallelSearchCall(const std::string& substr, const std::string& str, std::vector<std::size_t>& indices)
{
    std::mutex mutex;
    parallelSearch(substr, str, 0U, str.size() - substr.size() + 1, indices, mutex);
}

int main()
{

    std::string str = make_sequence(50);
    std::cout << str;
    std::cout << "\nEnter substr to find: ";
    std::string substr;
    std::cin >> substr;

    std::vector <std::size_t> ind;
    parallelSearchCall(substr, str, ind);

    std::sort(std::begin(ind), std::end(ind));

    std::cout << "The beginning of substr located on positions: ";

    for (auto i : ind)
    {
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    return 0;
}
