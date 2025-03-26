#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <cctype>
#include <algorithm>

void read_file(std::string filename, std::map<std::string, int>& map)
{
    std::ifstream file(filename);

    std::string word;
    while (file >> word)
    {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        map[word]++;
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

void save_to_csv(std::map<int, int> map)
{
    std::ofstream file("rank_map.csv");

    file << "Rank,Frequency\n";
    for (const auto& elem : map)
    {
        file << elem.first << "," << elem.second << "\n";
    }
    file.close();
}

int main()
{
    std::map<std::string, int> frequency_map;

    std::string filename = "text.txt";
    read_file(filename, frequency_map);
    size_t words_num = frequency_map.size();

    std::vector<std::pair<std::string, int>> frequency_vec_sort = sort_map(frequency_map);

    std::map<int, int> rank_map;
    int index = 1;
    for (const auto& elem : frequency_vec_sort)
    {
        rank_map[index++] = elem.second;
    }

    print_summary(rank_map, frequency_vec_sort);

    save_to_csv(rank_map);
}