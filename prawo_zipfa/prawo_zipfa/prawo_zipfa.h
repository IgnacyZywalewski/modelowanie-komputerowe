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
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());

        for (char& ch : word)
        {
            ch = std::tolower(ch, loc);
        }

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
