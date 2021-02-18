#include <algorithm>
#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <vector>

#include "Timer.hpp"
#define SIZE 1000000



int main(int argc, const char * argv[]) {
    std::vector<int> v(SIZE);
    std::array<int, SIZE> ar;
    std::deque<int> d(SIZE);
    std::list<int> l(SIZE);
    std::forward_list<int> fl(SIZE);

    //Заполнение
    for (auto& i : v)
    {
        i = rand()%10;
    }
    int k = 0;
    for (auto& i : ar)
    {
        i = v[k++];
    }
    k = 0;
    for (auto& i : d)
    {
        i = v[k++];
    }
    k = 0;
    for (auto& i : l)
    {
        i = v[k++];
    }
    k = 0;
    for (auto& i : fl)
    {
        i = v[k++];
    }


    // Замеры
    {
        Timer timer_v("Timer vector");
        std::sort(v.begin(), v.end());
    }
    {
        Timer timer_a("Timer array");
        std::sort(ar.begin(), ar.end());
    }
    {
        Timer timer_d("Timer deque");
        std::sort(d.begin(), d.end());
    }
    {
        Timer timer_l("Timer list");
        l.sort();
    }
    {
        Timer timer_fl("Timer forward_list");
        fl.sort();
    }

    return 0;
}
