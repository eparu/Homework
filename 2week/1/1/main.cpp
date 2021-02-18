#include <iostream>
#include <vector>
//Наблюдения в комментарии внизу

void PrintSizeAndCapacity (std::vector<int> &v)
{
    std::cout << "Size: " << v.size() << " Capacity: "<< v.capacity() << std::endl;
}

int main(int argc, const char * argv[]) {
    std::vector<int> v(7, 0);
    std::cout << "Begin\n";
    PrintSizeAndCapacity(v);

    v.push_back(0);
    std::cout << "One element added\n";
    PrintSizeAndCapacity(v);


    std::vector<int> v1(7, 0);
    v1.reserve(8);
    std::cout << "\nUsing reserve:\n";
    std::cout << "Begin\n";
    PrintSizeAndCapacity(v1);

    v1.push_back(0);
    std::cout << "One element added\n";
    PrintSizeAndCapacity(v1);

    v1.push_back(0);
    std::cout << "Two elements added\n";
    PrintSizeAndCapacity(v1);

    std::cout << "\nBig vector\n";
    std::vector<int> BigVector(7000000000);
    std::cout << "Begin\n";
    PrintSizeAndCapacity(BigVector);
    BigVector.push_back(0);
    std::cout << "One element added\n";
    PrintSizeAndCapacity(BigVector);

    std::cout << "Done!";
    return 0;
}


/*
 1) При нехватке памяти для размещения новых элементов
 емкость становится k*N,
 где N -- размер изначального вектора, а k = 2.
         Begin
         Size: 7 Capacity: 7
         One element added
         Size: 8 Capacity: 14

2) При использовании reserve для задания начальной емкости
 можно добавлять новые элементы до тех, пока размер вектора
 <= емкость вектора. Когда при добавлении нового элемента
 размер становится больше емкости происходит то же самое,
 что и в пункте 1).

         Using reserve:
         Begin
         Size: 7 Capacity: 8
         One element added
         Size: 8 Capacity: 8
         Two elements added
         Size: 9 Capacity: 16

 3) Если размер вектора очень большой и при добавлении
 нового элемента ресурсов ОС не хватает для увеличения
 емкости, то происходит ошибка:
         Big vector
         Begin
         Size: 8000000000 Capacity: 8000000000
         (lldb)

 */
