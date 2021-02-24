#include <iostream>
constexpr int H = 163;

/*
 1. Детерминированность: одному и тому же числу соответствует
 одно и то же возвращаемое значение (нет рандомности).
 2. Скорость вычисления не зависит от количества элементов,
 которые уже есть в хэш-таблице.
 3. Функция распределяет более менее равномерно ( для чисел
 в диапазоне от е-4 до е+4) за счет приведения к целому числу
 */

std::size_t hash(const double key)
{
    int answer = 0;
    for (int h = key * 10e4 ; h > 0; h /= 10)
    {
        answer = answer * 31 + h % 10;
    }

    return answer % H;
}

int main(int argc, const char * argv[]) {
    std::cout << hash(1.92) << std::endl;
    std::cout << hash(1.52e-4) << std::endl;
    std::cout << hash(1.52e4) << std::endl;

    return 0;
}
