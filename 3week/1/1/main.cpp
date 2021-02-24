#include <array>
#include <iostream>
#include <set>
#include <vector>

#include "Timer.hpp"
constexpr int N = 2000000;

// Быстрее выполняется сортировка последовательных контейнеров
// Не наблюдалось значений N, при которых работа set быстрее сортировки последовательного контейнера


int main(int argc, const char * argv[]) {

    std::set<int> set;
    {
        Timer Timer_a ("Timer for set");
        for (int i = N-1; i >= 0; i--)
        {
            set.insert(i);
        }
    }

    std::vector<int> v(N);
    {
        Timer Timer_v("Timer for vector");
        for (int i = N-1; i >= 0; i--)
        {
            v[i] = i;
        }
        std::sort(v.begin(), v.end());
    }

    std::array<int, N> ar;
    {
        Timer Timer_ar("Timer for std::array");
        for (int i = N-1; i >= 0; i--)
        {
            ar[i] = i;
        }
        std::sort(ar.begin(), ar.end());
    }


    return 0;
}
