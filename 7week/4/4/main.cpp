#include <execution>
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <numeric>

#include "Timer.hpp"



int main()
{
    std::cout << "N, par for_each, sec for_each, partial_sum, inclusive_scan, transform_reduce, inner_product\n";
    for (auto SIZE = 10000; SIZE < 1000000; SIZE += 10000)
    {
        std::vector < int > v(SIZE);
        std::mt19937_64 gen;
        std::uniform_real_distribution <> uid(0, 100);
        std::cout << SIZE <<" , ";


        {
            Timer t("par for_each");
            std::for_each (std::execution::par, std::begin(v), std::end(v), [&uid, &gen](auto &x) { x = uid(gen);
            });
        }
        std::cout <<", ";

        {
            Timer t("seq for_each");
            std::for_each (std::begin(v), std::end(v), [&uid, &gen](auto &x) {
                x = uid(gen);
            });
        }
        std::cout <<", ";

        std::vector<int> v1(v.size());
        {
            Timer t("partial_sum" );
            std::partial_sum(v.begin(), v.end(), v1.begin(), std::plus<int>());
        }
        std::cout <<", ";


        {
            Timer t("inclusive_scan" );
            std::inclusive_scan(std::execution::par, v.begin(), v.end(), v1.begin(), std::plus<int>());
        }
        std::cout <<", ";


        {
            Timer t("transform_reduce" );
            int r = std::transform_reduce(std::execution::par, std::begin(v), std::end(v), std::begin(v1), 0);
        }
        std::cout <<", ";
        {
            Timer t("inner_product" );
           int r = std::inner_product(std::begin(v), std::end(v), std::begin(v1), 0);
        }
        std::cout << std::endl;
    }
    return 0;
}
