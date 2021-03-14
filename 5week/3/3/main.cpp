#include <iostream>
#include <regex>
#include <string>
#include <sstream>



int main(int argc, char** argv)
{
    std::string data = "e-mail address example@com, a..t@mail.ru, aa@mail.mipt.ru, aa.aa.aa@gmail.com, a.a.@mail.ru, a.a@mail.ru, .A.mail.ru, 89499, 9-0";
    std::regex pattern(R"((\w+(?:\.\w+)*)@(\w+(?:\.\w+)*))");

    std::sregex_iterator begin(std::begin(data), std::end(data), pattern);
    std::sregex_iterator end;

    std::for_each(begin, end, [](const std::smatch& m)
    {
        std::cout << m[0] << " -- " << m[2] << std::endl;
    });
    return 0;
}
