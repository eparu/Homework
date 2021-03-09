#include <iostream>
#include <iomanip>
#include <locale>


long double convert_dollars_to_rubles(long double dollars){
    return dollars * 73.86;
}


int main()
{

    std::locale locale_rus("ru_RU.UTF-8");
    std::locale locale_us("en_US.UTF-8");

    long double dol;
    std::cout << "Enter dollars: ";

    std::cin.imbue(locale_us);
    std::cin >> std::get_money(dol);

    auto rub = convert_dollars_to_rubles(dol);

    std::cout.imbue(locale_us);
    std::cout << std::showbase << std::put_money(dol) << " - ";
    std::cout.imbue(locale_rus);
    std::cout << std::showbase << std::put_money(rub) << std::endl;

    return 0;
}
