#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cctype>
#include <locale>
#include <algorithm>
#include <windows.h>


void read_file(std::string filename, std::map<std::string, int>& map)
{
    std::locale loc("pl_PL.utf8");
    std::ifstream file("teksty/" + filename + ".txt");
    std::string word;

    while (file >> word)
    {
        std::string clean;

        for (char ch : word)
        {
            if (std::isalpha(static_cast<unsigned char>(ch), loc) || std::string("ąćęłńóśźżĄĆĘŁŃÓŚŹŻ").find(ch) != std::string::npos)
            {
                clean += std::tolower(static_cast<unsigned char>(ch), loc);
            }
        }

        word = clean;

        if (!word.empty())
        {
            map[word]++;
        }
    }

    file.close();
}


template <typename Y>
void print_map(Y map)
{
    for (const auto& elem : map)
    {
        std::cout << elem.first << ", " << elem.second << "\n";
    }
    std::cout << "\n";
}


void print_summary(std::map<int, int>& map, std::vector<std::pair<std::string, int>>& vec)
{
    int i = 0;
    for (const auto& elem : map)
    {
        std::cout << "ranga = " << elem.first << ", slowo: " << vec[i].first << ", ilosc wystapien = " << elem.second << "\n";
        i++;
    }
}


std::vector<std::pair<std::string, int>> sort_map(std::map<std::string, int> map)
{
    std::vector<std::pair<std::string, int>> vector(map.begin(), map.end());

    std::sort(vector.begin(), vector.end(), [](const auto& a, const auto& b) { return a.second > b.second; });

    return vector;
}
