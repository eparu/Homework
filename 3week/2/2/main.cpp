#include <bitset>
#include <iostream>
constexpr int H = 163;

/*
 1. Детерминированность: одному и тому же числу соответствует
 одно и то же возвращаемое значение (нет рандомности).
 2. Скорость вычисления не зависит от количества элементов,
 которые уже есть в хэш-таблице.
 3. Функция распределяет более менее равномерно за счет
 использования битов числа double
 */

std::size_t hash(const double key)
{
    auto b = std::bitset <64> (*(unsigned long long*)(&key));
    b = ((b >> 13) ^ (b << 17) ^ (b >> 31) ^ (b << 3));
    auto answer = std::bitset < 64 > (b).to_ullong();
    return answer % H;
}

int main(int argc, const char * argv[]) {
    std::cout << hash(1.92) << std::endl;
    std::cout << hash(1.91) << std::endl;
    std::cout << hash(-1.92) << std::endl;

    std::cout << hash(8.0) << std::endl;
    std::cout << hash(1.62e+8) << std::endl;
    std::cout << hash(-1.62e+308) << std::endl;
     std::cout << hash(1.48e-300) << std::endl;

    std::cout << hash(1.52e-4) << std::endl;
    std::cout << hash(-1.52e-4) << std::endl;
    std::cout << hash(1.51e-4) << std::endl;
    std::cout << hash(1.52e-3) << std::endl;


    return 0;
}
