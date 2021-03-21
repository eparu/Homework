#include <iostream>
#include <iomanip>
#include <fstream>

int main(int argc, const char * argv[]) {
//    std::fstream fout("file.txt", std::ios::out);
//    for (int i = 1; i < 21; i++){
//        fout.fill('0');
//        fout << "string" << std::setw(2) << i << std::endl;
//    }
//    fout.close();

    std::fstream fin("file.txt", std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "File was not found\n";
        return 0;
    }

    std::size_t number_of_string;
    std::cout << "Enter number of string to search: ";
    std::cin >> number_of_string;

    std::string s;
    if (std::getline(fin, s))
    {
        if (number_of_string != 1)
        {
            fin.seekg((number_of_string - 1)*(s.size() + 1), std::ios::beg);
            if (!std::getline(fin, s))
            {
                std::cout << "No strings with this number\n";
                return 0;
            }
        }
        std::cout << s << std::endl;
    }
    else
    {
        std::cout << "There are no strings in file\n";
    }
    return 0;
}
