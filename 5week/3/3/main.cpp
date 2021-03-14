#include <iostream>
#include <regex>
#include <string>
#include <sstream>



int main(int argc, char** argv)
{
    std::string data = "e-mail address example@com, a..t@mail.ru, aa@mail.mipt.ru, aa.aa.aa@gmail.com, a.a.@mail.ru, a.a@mail.ru, .A.mail.ru, 89499, 9-0";
    std::regex pattern(R"(\w+(?:\.\w+)*@\w+(?:\.\w+)*)");


    std::copy(
              std::sregex_token_iterator(data.begin(), data.end(), pattern, { 0 }),
              std::sregex_token_iterator(),
              std::ostream_iterator < std::string >(std::cout, "\n"));

    return 0;
}
