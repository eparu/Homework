#include <iostream>
#include <iterator>
#include <locale>
#include <string>
#include <sstream>
#include <unordered_map>

#include <boost/locale.hpp>

#include <Windows.h>

std::string locale_to_utf8(const std::string & string)
{
    boost::locale::generator generator;
    generator.locale_cache_enabled(true);

    std::locale locale = generator(boost::locale::util::get_system_locale());

    return boost::locale::conv::to_utf < char >(string, locale);
}

std::string utf8_to_locale(const std::string& string)
{
    boost::locale::generator generator;
    generator.locale_cache_enabled(true);

    std::locale locale = generator(boost::locale::util::get_system_locale());

    return boost::locale::conv::from_utf < char >(string, locale);
}

std::u32string utf8_to_utf32 (const std::string& str)
{
    return boost::locale::conv::utf_to_utf < char32_t, char >(str);
}

std::string utf32_to_utf8 (const std::u32string& str)
{
    return boost::locale::conv::utf_to_utf < char, char32_t >(str);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::unordered_map<char32_t, std::u32string> table;

    table[U'А'] = U"A";
    table[U'Б'] = U"B";
    table[U'В'] = U"V";
    table[U'Г'] = U"G";
    table[U'Д'] = U"D";
    table[U'Е'] = U"E";
    table[U'Ё'] = U"E";
    table[U'Ж'] = U"Zh";
    table[U'З'] = U"Z";
    table[U'И'] = U"I";
    table[U'Й'] = U"I";
    table[U'К'] = U"K";
    table[U'Л'] = U"L";
    table[U'М'] = U"M";
    table[U'Н'] = U"N";
    table[U'О'] = U"O";
    table[U'П'] = U"P";
    table[U'Р'] = U"R";
    table[U'С'] = U"S";
    table[U'Т'] = U"T";
    table[U'У'] = U"U";
    table[U'Ф'] = U"F";
    table[U'Х'] = U"Kh";
    table[U'Ц'] = U"Ts";
    table[U'Ч'] = U"Ch";
    table[U'Ш'] = U"Sh";
    table[U'Щ'] = U"Shch";
    table[U'Ъ'] = U"'";
    table[U'Ы'] = U"Y";
    table[U'Ь'] = U"'";
    table[U'Э'] = U"E";
    table[U'Ю'] = U"Yu";
    table[U'Я'] = U"Ya";

    table[U'а'] = U"a";
    table[U'б'] = U"b";
    table[U'в'] = U"v";
    table[U'г'] = U"g";
    table[U'д'] = U"d";
    table[U'е'] = U"e";
    table[U'ё'] = U"e";
    table[U'ж'] = U"zh";
    table[U'з'] = U"z";
    table[U'и'] = U"i";
    table[U'й'] = U"i";
    table[U'к'] = U"k";
    table[U'л'] = U"l";
    table[U'м'] = U"m";
    table[U'н'] = U"n";
    table[U'о'] = U"o";
    table[U'п'] = U"p";
    table[U'р'] = U"r";
    table[U'с'] = U"s";
    table[U'т'] = U"t";
    table[U'у'] = U"u";
    table[U'ф'] = U"f";
    table[U'х'] = U"kh";
    table[U'ц'] = U"ts";
    table[U'ч'] = U"ch";
    table[U'ш'] = U"sh";
    table[U'щ'] = U"shch";
    table[U'ъ'] = U"'";
    table[U'ы'] = U"y";
    table[U'ь'] = U"'";
    table[U'э'] = U"e";
    table[U'ю'] = U"yu";
    table[U'я'] = U"ya";

    std::string str;
    std::u32string u32_ru_str;
    std::u32string u32_en_str;

    std::stringstream ss;
    ss << "Первая строка\n" << "157 - Сто пятьдесят семь\n";

    while (std::getline(ss, str))
    {
        std::cout << str << std::endl;
        str = locale_to_utf8(str);

        u32_ru_str = utf8_to_utf32(str);

        for (auto& elem : u32_ru_str)
        {
            if (elem >= U'А' && elem <= U'я')
            {
                std::copy(std::begin(table[elem]), std::end(table[elem]), std::back_inserter(u32_en_str));
            }
            else
            {
                u32_en_str.push_back(elem);
            }
        }

        str = utf32_to_utf8(u32_en_str);
        str = utf8_to_locale(str);
        std::cout << str << std::endl;
        str.clear();
    }
    return 0;
}
