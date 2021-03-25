#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <fstream>
#include <vector>

/*
 Оптимальнное значение N количества потоков зависит от размера вектора SIZE (см. graph).
 В среднем оптимальные значения N лежат в диапозоне от 1 до 4 (см. graph_scaled)
 При увеличении количества потоков в целом наблюдается рост времени. (см. graph_for_100)
 */

#include "Timer.hpp"

class Threads_Guard
{
public:

    explicit Threads_Guard(std::vector < std::thread > & threads) :
    m_threads(threads)
    {}

    Threads_Guard            (Threads_Guard const&) = delete;

    Threads_Guard& operator=(Threads_Guard const&) = delete;

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

template < typename Iterator, typename T >
struct accumulate_block
{
    T operator()(Iterator first, Iterator last)
    {
        return std::accumulate(first, last, T());
    }
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, std::size_t custom_threads)
{
    const std::size_t length = std::distance(first, last);

    if (!length) return init;

    const std::size_t num_threads = custom_threads;

    const std::size_t block_size = length / num_threads;

    std::vector < std::future < T > > futures(num_threads - 1);
    std::vector < std::thread >          threads(num_threads - 1);

    Threads_Guard guard(threads);

    Iterator block_start = first;

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        Iterator block_end = block_start;
        std::advance(block_end, block_size);

        std::packaged_task < T(Iterator, Iterator) > task{
            accumulate_block < Iterator, T >() };

        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_start, block_end);

        block_start = block_end;
    }

    T last_result = accumulate_block < Iterator, T > ()(block_start, last);

    T result = init;

    for (std::size_t i = 0; i < (num_threads - 1); ++i)
    {
        result += futures[i].get();
    }

    result += last_result;

    return result;
}

int main(int argc, char ** argv)
{
    std::fstream fout("results.csv", std::ios::out);
    fout << "SIZE, N\n";
    for (auto SIZE = 0U; SIZE < 1000000; SIZE += 1000)
    {
        std::vector < int > v(SIZE);

        std::iota(v.begin(), v.end(), 1);

        std::size_t min_t = LONG_LONG_MAX;
        std::size_t N = 0;

        for (std::size_t threads = 1; threads <= 50; threads += 1)
        {
            Timer t;
            parallel_accumulate(v.begin(), v.end(), 0, threads);
            t.Stop();
           // std::cout << threads << ", " << t.convert_into_number() << std::endl;
            if (min_t > t.convert_mic_into_number())
            {
                min_t = t.convert_mic_into_number();
                N = threads;
            }
        }
        fout << SIZE << " ," << N << std::endl;
      //  std::cout << SIZE << " ," << N << std::endl;

    }
    fout.close();


    return 0;
}

