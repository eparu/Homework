#include <iostream>
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <execution>

#include "Timer.hpp"

inline bool in_circle(const double& x, const double& y)
{
    return (x*x + y*y < 1);
}


double sequential_pi(const std::size_t amount_of_points)
{
    std::mt19937_64 gen;
    std::uniform_real_distribution <> urd(0.0, 1.0);
    std::size_t points_in_circle = 0;

    for (auto i = 0U; i < amount_of_points; i++) {
        if (in_circle(urd(gen), urd(gen))) points_in_circle++;
    }
    return points_in_circle*4.0 / amount_of_points;
}


double parallel_pi(const std::size_t amount_of_points)
{
    std::mt19937_64 gen;
    std::uniform_real_distribution <> urd(0.0, 1.0);
    std::vector <std::pair<double, double>> points(amount_of_points);


    std::for_each (std::execution::par, std::begin(points), std::end(points), [&urd, &gen](auto &p) {
    p.first = urd(gen);
    p.second = urd(gen);
});

//    std::for_each (std::begin(points), std::end(points), [&urd, &gen](auto &p) {
//        p.first = urd(gen);
//        p.second = urd(gen);
//    });

    std::size_t points_in_circle = std::count_if(std::execution::par,
                    std::begin(points), std::end(points), [](const auto& p) {return in_circle(p.first, p.second);
                    });
//    std::size_t points_in_circle = std::count_if(
//                        std::begin(points),
//                        std::end(points),
// [](const auto& p) {return in_circle(p.first, p.second);
//                        });


    return points_in_circle*4.0 / amount_of_points;
}


int main(int argc, const char * argv[]) {
    for (auto i = 100000; i <=  10000000; i+= 500000)
    {
        {
            Timer t1("Sequential PI");
            double PI = sequential_pi(i);
            t1.Print();
        }

        {
            Timer t("Parallel PI");
            double PI = parallel_pi(i);
            t.Print();
        }
        std::cout << std::endl;
    }
    return 0;
}
