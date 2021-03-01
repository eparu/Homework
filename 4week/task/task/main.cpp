
#include <iostream>
#include <iomanip>
#include <chrono>
#include <numeric>
#include <random>
#include <vector>


void Print_vector (const std::vector <int> & v, const std::string & msg = "")
{
    if (std::size(msg) > 1)
    {
        std::cout << std::left << std::setw(23) << msg;
    }
    if (std::size(msg) == 3)
    {
        std::cout << msg;
    }
    std::for_each(std::begin(v), std::end(v), [](auto x) {std::cout << x << ' '; });
    std::cout << std::endl;
}


int main(int argc, const char * argv[]) {
    std::vector <int> v1(10);

    // #1 Создание последовательности П1 целых чисел от 1 до 10
    int k = 1;
    std::generate_n(std::begin(v1), 10, [&k]() {return k++;});
    Print_vector(v1, "Creation v1:");

    // #2 Добавление нескольких чисел в конец П1 из cin
    std::cout << "Enter numbers to add and Ctrl+D (Ctrl+Z):\n";
    std::copy(
              std::istream_iterator < int > (std::cin),
              std::istream_iterator < int > (),
              std::back_inserter(v1));
    Print_vector(v1, "Numbers added v1: ");

    //#3 Перемешать П1 случайным образом
    std::default_random_engine  dre(std::chrono::system_clock().now().time_since_epoch().count());
    std::mt19937_64 g(dre());
    std::shuffle(std::begin(v1), std::end(v1), g);
    Print_vector(v1, "Shuffle v1: ");

    //#4 Удаление дубликатов
    std::sort(std::begin(v1), std::end(v1));
    auto erase_part = std::unique(std::begin(v1), std::end(v1));
    v1.erase(erase_part, std::end(v1));
    Print_vector(v1, "Duplicates removed v1: ");

    //#5 Подсчет количества нечетных чисел
    auto result = std::count_if(std::begin(v1), std::end(v1), [](auto x) {return !(x % 2 == 0);});
    std::cout << "Amount of odd numbers: " << result << std::endl;

    //#6 Определение минимального и максимального числа в П1
    auto [min, max] = std::minmax_element(std::begin(v1), std::end(v1));
    std::cout << "Min element v1: " << *min << std::endl;
    std::cout << "Max element v1: " << *max << std::endl;

    //#7 Поиск хотя бы одного простого числа в П1
    auto it = std::find_if(std::begin(v1), std::end(v1), [](auto x){
            if ((x % 2 == 0 && x != 2 )|| x <= 1) return false;
            for (auto i = 3; i <= sqrt(x); i += 2 )
            {
                if (x % i == 0) return false;
            }
            return true;
    });

    if (it != std::end(v1))
    {
        std::cout << "Prime number: " << *it << '\n';
    }
    else
    {
        std::cout << "Prime number was not found\n";
    }

    //#8 Замена всех чисел в П1 их квадратами
    std::for_each(std::begin(v1), std::end(v1), [](auto& x) {x *= x;});
    Print_vector(v1, "Squares v1: ");

    //#9 Создание последовательности П2 из N случайных чисел, где N = П1.size();
    std::vector <int> v2(v1.size());
    std::uniform_int_distribution <> uid(0, 20);
    std::default_random_engine  dre1(std::chrono::system_clock().now().time_since_epoch().count());
    std::generate_n(std::begin(v2), v1.size(), [&dre1, &uid] () {return uid(dre1);});
    Print_vector(v2, "Random v2: ");

    //#10 Вычисление суммы чисел в П2
    auto sum = std::accumulate(std::begin(v2), std::end(v2), 0);
    std::cout << "Sum of v2: " << sum << std::endl;

    //#11 Заменить первые несколько чисел в П2 числом 1
    std::fill_n(std::begin(v2), 17%std::size(v2), 1);
    Print_vector(v2, "Replace with 1 in v2: ");

    //#12 Создать последовательность П3 как разность П1 и П2
    std::vector<int> v3;
    std::copy(std::begin(v1), std::end(v1), std::back_inserter(v3));
    std::transform(std::begin(v3), std::end(v3), std::begin(v2), std::begin(v3), std::minus());
    Print_vector(v3, "Creation v3: ");

    //#13 Заменить каждый отрицательный элементы в П3 нулем
    std::replace_if(std::begin(v3), std::end(v3),  [] (auto x) {return x < 0;}, 0);
    Print_vector(v3, "Replace - to 0 in v3: ");

    //#14 Удалить все нулевые элементы из П3
    v3.erase(std::remove_if(std::begin(v3), std::end(v3), [](auto x){return x == 0;}), std::end(v3));
    Print_vector(v3, "Delete 0 in v3: ");

    //#15 Изменить порядок следования элементов в П3 на обратный
    std::reverse(std::begin(v3), std::end(v3));
    Print_vector(v3, "Reverse v3: ");

    //#16 Определите быстро топ-3 наибольших элемента в П3
    if (std::size(v3) < 3)
    {
        std::cout << "Top-3 can't be identified\n";
    }
    else
    {
        std::cout << "Top-3 in v3: ";
        std::nth_element(std::begin(v3), std::prev(std::end(v3), 1), std::end(v3));
        std::cout << v3[v3.size() - 1] << ' ';
        std::nth_element(std::begin(v3), std::prev(std::end(v3), 2), std::end(v3));
        std::cout << v3[v3.size() - 2] << ' ';
        std::nth_element(std::begin(v3), std::prev(std::end(v3), 3), std::end(v3));
        std::cout << v3[v3.size() - 3] << std::endl;
    }

    //#17 Отсортируйте П1 и П2 по возрастанию
    std::sort(std::begin(v1), std::end(v1));
    Print_vector(v1, "v1 sorted: ");

    std::sort(std::begin(v2), std::end(v2));
    Print_vector(v2, "v2 sorted: ");

    //#18 Создание последовательности П4 как слияние П1 и П2
    std::vector < int > v4 (std::size(v1) + std::size(v2));
    std::merge(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::begin(v4));
    Print_vector(v4, "v4 = merge(v1, v2): ");

    //#19 Определите диапазон для упорядоченной вставки числа 1 в П4
    auto place = std::equal_range(std::begin(v4), std::end(v4), 1);
    std::cout << *place.first << std::endl;
    std::cout << *place.second << std::endl;


    //#20 Выведите все последовательности в cout
    Print_vector(v1, "v1: ");
    Print_vector(v2, "v2: ");
    Print_vector(v3, "v3: ");
    Print_vector(v4, "v4: ");






    return 0;
}
