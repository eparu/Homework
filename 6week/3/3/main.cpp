#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>


template <typename T>
std::time_t to_time_t(T time_point)
{
    auto system_clock_time_point = std::chrono::time_point_cast<std::chrono::system_clock::duration>(time_point - T::clock::now()
                                                                                                     + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(system_clock_time_point);
}


void view_directory(const std::filesystem::path& path)
{
    if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
    {
        for (const auto & entry : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_directory(entry))
            {
                std::cout << "dir    ";
            }
            else
            {
                std::cout << "file   ";
            }
            auto file_name = entry.path().filename().string();
            auto ftime = std::filesystem::last_write_time(path);
            auto extension = entry.path().extension().string();
            std::time_t cftime = to_time_t(ftime);

            std::cout << std::left << std::setw(30) << file_name << std::setw(10) << extension << std::setw(20) << std::asctime(std::localtime(&cftime)) << std::endl;
        }
    }
}

int main(int argc, const char** argv)
{
    ("chcp 1251");
    std::filesystem::path path;
    std::cout << "Enter the path: ";
    std::cin >> path;
    view_directory(path);


    return 0;
}
