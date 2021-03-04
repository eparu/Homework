#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>


int main(int argc, const char * argv[]) {
    std::ofstream fout("results.csv");
    fout << "SIZE, sort, nth_element\n";
    for (auto SIZE = 5000U; SIZE <= 1'000'000; SIZE += 5000)
    {
        std::vector<int> v1 (SIZE);
        std::vector<int> v2;

        std::default_random_engine dre(std::chrono::system_clock().now().time_since_epoch().count());
        std::uniform_int_distribution <> uid(0, 100);
        std::generate_n(std::begin(v1), SIZE, [&dre, &uid]() {return uid(dre); });
        std::copy(std::begin(v1), std::end(v1), std::back_inserter(v2));

        int counter1 = 0;
        std::sort(std::begin(v1), std::end(v1),
                  [&counter1](auto x, auto y){
                      counter1++;
                      return x < y;
                  });



        int counter2 = 0;
        std::nth_element(std::begin(v2), std::prev(std::end(v2), 2), std::end(v2),
                         [&counter2](auto x, auto y){
                             counter2++;
                             return x < y;
                         });

        fout << SIZE << ',' << counter1 << ',' << counter2 << std::endl;
       // std::cout << SIZE << ',' << counter1 << ',' << counter2 << std::endl;
    }
    fout.close();
    return 0;
}
