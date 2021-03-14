#include <iostream>
#include <regex>

//YYYY.MM.DD or HH:MM:SS

int main(int argc, const char * argv[]) {
    std::string data = "Today: 2021.03.14 heheh, 12:00:77, 1.12.6, 000.12.30, 0001.00.30, 1001.01.30, 1000.13.01, 12:00:00, 67:01.00, 0057.787.30, 10:56:60, 12:00";

    std::regex pattern(R"((\d{4}\.(0[1-9]|1[012])\.(0[1-9]|1\d|2\d|3[01]))|(([0-1]\d|2[0-3])(\:[0-5]\d){2}))");

    std::sregex_iterator begin(std::begin(data), std::end(data), pattern);
    std::sregex_iterator end;

    std::for_each(begin, end, [](const std::smatch& m)
    {
        if (static_cast<std::string>(m[1]).size() != 0)
        {
            std::cout << "Date: " << m[1] << std::endl;
        }
        else if (static_cast<std::string>(m[4]).size() != 0)
        {
            std::cout << "Time: " << m[4] << std::endl;
        }
    });
    return 0;
}
