#include <future>
#include <iostream>
#include <random>
#include <thread>
#include <vector>


inline bool in_circle(const double& x, const double& y)
{
    return (x*x + y*y < 1);
}


class Threads_Guard
{
public:
    explicit Threads_Guard(std::vector < std::thread > & threads) : m_threads(threads)
    {}

    Threads_Guard(Threads_Guard const&) = delete;

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
            std::cerr << "\nDTOR THREAD ERROR\n";
        }
    }

private:
    std::vector < std::thread >& m_threads;
};


struct counter_in_circle
{
    std::size_t operator()(const std::size_t N, std::atomic<std::size_t> &points_in_circle)
    {
        std::mt19937_64 gen;
        std::uniform_real_distribution <> urd(0.0, 1.0);;
        for (auto i = 0U; i < N; ++i)
        {
            if (in_circle(urd(gen), urd(gen)))
                points_in_circle++;
        }
        return points_in_circle++;
    }
};

double parallel_pi(const std::size_t amount_of_points)
{
    const std::size_t hardware_threads = std::thread::hardware_concurrency();
    const std::size_t num_threads =(hardware_threads != 0 ? hardware_threads : 2);
    const std::size_t block_size = amount_of_points / num_threads;
    

    std::vector < std::future < void > > futures(num_threads - 1);
    std::vector < std::thread > threads(num_threads - 1);

    Threads_Guard guard(threads);

    std::atomic<std::size_t> points_in_circle = 0;

    for (auto i = 0; i < (num_threads - 1); ++i)
    {
        std::packaged_task < void(const std::size_t, std::atomic<std::size_t>&) > task{counter_in_circle()};

        futures[i] = task.get_future();
        threads[i] = std::thread(std::move(task), block_size, std::ref(points_in_circle));
    }

   counter_in_circle()(amount_of_points - (num_threads - 1) * block_size, points_in_circle);

    for (auto i = 0U; i < (num_threads - 1); ++i)
    {
        futures[i].get();
    }

    return points_in_circle*4.0 / amount_of_points;
}


int main(int argc, const char * argv[]) {
    constexpr std::size_t N = 10000000;
    {
        double PI = parallel_pi(N);
        std::cout << PI << std::endl;
    }
    return 0;
}
