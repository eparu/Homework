#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

template < typename Iterator, typename F >
void parallel_for_each(Iterator first, Iterator last, F function)
{
    const std::size_t length = std::distance(first, last);

    const std::size_t max_size = 100'000;

    if (length <= max_size)
    {
        std::for_each(first, last, function);
    }
    else
    {
        Iterator middle = first;
        std::advance(middle, length / 2);

        std::future < void > first_half_result = std::async(parallel_for_each < Iterator, F >, first, middle, function);

        parallel_for_each(middle, last, function);
        first_half_result.get();
    }
}

int main()
{
    std::vector < int > v(100000000, 1);

    parallel_for_each(std::begin(v), std::end(v), [](auto& x) {x += 10;});
  //  std::cout << v[0] << std::endl;

    return 0;
}

