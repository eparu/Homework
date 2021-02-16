/*
 Отличия между Rebase и Merge:
 1. Merge сливает содержимое ветки1 в ветку2, не меняя истории ветки1. История полностью сохраняется, но она "загрязненяется" множеством коммитов, что не всегда удобно.
 2. Rebase перетягивает начало ветки2 до состояния новейшей версии ветки1. История меняется (упрощается), но становится непонятно, откуда началась разработка ветки2.
*/

#include <iostream>

int main(int argc, const char * argv[]) {
    std::cout << "Commit in master\n";
    std::cout << "Hello, World!\n";
    return 0;
}

int g(int a){
    std::cout << a;
}
// Second change in New branch
// Commit in master
// Commit in New2 branch
//Second commit in New2 branch
