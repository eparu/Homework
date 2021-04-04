#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <chrono>
#include <random>
#include <thread>
#include <vector>
#include <map>

std::string make_sequence(std::size_t N)
{
    std::uniform_int_distribution <> uid(0, 4);
    std::default_random_engine dre(static_cast < std::size_t > (std::chrono::system_clock::now().time_since_epoch().count()));
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


class Threads_Guard
{
public:

    explicit Threads_Guard(std::vector < std::thread > & threads) :
    m_threads(threads)
    {}

    Threads_Guard(Threads_Guard const &) = delete;

    Threads_Guard& operator=(Threads_Guard const &) = delete;

    ~Threads_Guard() noexcept
    {
        try
        {
            for (std::size_t i = 0; i < m_threads.size(); ++i)
            {
                if (m_threads[i].joinable())
                {
                    m_threads[i].join();
                }
            }
        }
        catch (...)
        {
            // std::abort();
        }
    }

private:

    std::vector < std::thread > & m_threads;
};


template < typename Iterator >
struct Searcher
{
    void operator()(Iterator first, Iterator last, Iterator first_search, Iterator last_search, std::promise < Iterator > & result, std::atomic < bool > & flag) noexcept
    {
        try
        {
            for (; (first != last) && (first_search != last_search) && !flag.load(); ++first, ++first_search)
            {
                if (*first != *first_search)
                {
                    return;
                }
            }
            result.set_value(first);
            flag.store(true);
            return;
        }
        catch (...)
        {
            try
            {
                result.set_exception(std::current_exception());
                flag.store(true);
            }
            catch (...)
            {
                // ...
            }
        }
    }
};

template < typename Iterator >
Iterator parallel_find(Iterator first, Iterator last, Iterator first_search, Iterator last_search )
{
    const std::size_t length = std::distance(first, last);

    if (!length)
        return last;

    const std::size_t min_per_thread = 25;
    const std::size_t max_threads =
    (length + min_per_thread - 1) / min_per_thread;

    const std::size_t hardware_threads =
    std::thread::hardware_concurrency();

    const std::size_t num_threads =
    std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    const std::size_t block_size = length / num_threads;

    std::atomic < std::size_t > result;
    std::atomic < bool > flag(false);
    std::vector < std::thread > threads(num_threads - 1);

    {
        Threads_Guard guard(threads);

        Iterator block_start = first;

        for (std::size_t i = 0; i < (num_threads - 1); ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);

            threads[i] = std::thread(Searcher < Iterator>(),
                                     block_start, block_end, first_search, last_search, std::ref(result), std::ref(flag));
            block_start = block_end;
        }

        Searcher < Iterator> ()(block_start, last, first_search, last_search, result, flag);
    }

    if (!flag.load())
    {
        return last;
    }

    return result.get_future().get();
}

int main(int argc, char ** argv)
{
    constexpr std::size_t N = 10;
    std::string big_string = make_sequence(N);
    std::cout << big_string;
    std::cout << "Enter string to search: ";

    std::string string_to_search;
    std::cin >> string_to_search;

    auto result = parallel_find(big_string.begin(), big_string.end(), string_to_search.begin(), string_to_search.end());

    if (result.size() != 0)
    {
        std::cout << "Index number: ";
        for (auto &i : result)
        {
            std::cout << i << " ";
        }
    }
    else
    {
        std::cout << "String not found" << std::endl;
    }


    return 0;
}

