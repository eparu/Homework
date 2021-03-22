#include <iostream>
#include <fstream>
#include <iomanip>

#include <boost/filesystem.hpp>

#include "json.hpp"

using nlohmann::json;


struct Person
{
    std::string name;
    unsigned int height;
    bool tired;
};


std::istream & operator>>(std::istream &input, Person& p)
{
    input >> p.name >> p.height >> p.tired;
    return input;
}

json convert_to_json(const Person &p)
{
    json j;
    j["name"] = p.name;
    j["height"] = p.height;
    j["tired"] = p.tired;
    return j;
}

void OutputInFile(const std::string& path_string, const json& j, const std::string& file_name)
{
     std::ofstream fout(path_string + "/" + file_name);
    if (fout.is_open())
    {
        fout << j.dump(3);
        std::cout << j.dump(3);
        fout.close();
    }
    else
    {
        std::cout << "Error\n";
    }
}

std::string CreateDirectory(const boost::filesystem::path& path, const std::string& folder_name)
{
    boost::filesystem::create_directory(path / folder_name);
    return path.string() + folder_name;
}

int main(int argc, const char * argv[]) {

    Person PeopleInMyRoom[2];
    std::cin >> PeopleInMyRoom[0];
    std::cin >> PeopleInMyRoom[1];

    json j1 = convert_to_json(PeopleInMyRoom[0]);
    json j2 = convert_to_json(PeopleInMyRoom[1]);


    auto path = boost::filesystem::current_path();
    std::string path_string = CreateDirectory(path, "folder");

    OutputInFile(path_string, j1, PeopleInMyRoom[0].name + ".txt");
    OutputInFile(path_string, j2, PeopleInMyRoom[1].name + ".txt");


    return 0;
}
