#include "prawo_zipfa.h"

struct Text {
    std::map<std::string, int> frequency_map;
    std::vector<std::pair<std::string, int>> frequency_vec_sort;
    std::map<int, int> rank_map;
};

void save_to_csv(std::map<std::string, std::map<int, int>> all_maps)
{
    std::ofstream file("rank_map.csv");

    file << "Rank";
    for (const auto& [text_name, _] : all_maps)
    {
        file << "," << text_name;
    }
    file << "\n";

    int max_rank = 0;
    for (const auto& [_, rank_map] : all_maps)
    {
        if (!rank_map.empty())
        {
            int last_rank = rank_map.rbegin()->first;
            if (last_rank > max_rank) {
                max_rank = last_rank;
            }
        }
    }

    for (int rank = 1; rank < max_rank; rank++)
    {
        file << rank;
        for (const auto& [text_name, rank_map] : all_maps)
        {
            if (rank_map.count(rank))
            {
                file << "," << rank_map.at(rank);
            }
            else
            {
                file << ",0";
            }
        }
        file << "\n";
    }
    file.close();
}

void analize_text(std::string filename, Text& text, std::map<std::string, std::map<int, int>>& all_maps)
{
    read_file(filename, text.frequency_map);
    text.frequency_vec_sort = sort_map(text.frequency_map);

    int index = 1;
    for (const auto& elem : text.frequency_vec_sort)
    {
        text.rank_map[index++] = elem.second;
    }

    //print_summary(text.rank_map, text.frequency_vec_sort);

    all_maps[filename] = text.rank_map;
}

int main()
{
    SetConsoleOutputCP(65001);

    std::map<std::string, std::map<int, int>> all_maps;

    Text pan_tadeusz;
    Text romeo_i_julia;

    analize_text("pan_tadeusz", pan_tadeusz, all_maps);
    analize_text("romeo_i_julia", romeo_i_julia, all_maps);

    save_to_csv(all_maps);

}