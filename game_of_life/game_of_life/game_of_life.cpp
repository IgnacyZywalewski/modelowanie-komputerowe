#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <fstream>
#include <filesystem>
#include <iomanip>

struct Cell
{
    Cell(bool alive) : alive(alive) {}

    bool is_alive() const { return alive; }
    void set_state(bool new_state) { alive = new_state; }

private:
    bool alive;
};

void randomize_board(std::vector<std::vector<Cell>>& board, std::mt19937& gen, double alive_probability = 0.5)
{
    std::bernoulli_distribution dist(alive_probability);
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            board[i][j].set_state(dist(gen));
        }
    }
}

int count_alive_neighbors(const std::vector<std::vector<Cell>>& board, int x, int y)
{
    int alive_neighbors = 0;
    size_t w = board.size();
    size_t h = board[0].size();

    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0) continue;

            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < w && ny >= 0 && ny < h)
            {
                if (board[nx][ny].is_alive())
                {
                    alive_neighbors++;
                }
            }
        }
    }
    return alive_neighbors;
}

void update_board(std::vector<std::vector<Cell>>& old_board, std::vector<std::vector<Cell>>& new_board)
{
    size_t w = old_board.size();
    size_t h = old_board[0].size();

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            int alive_neighbors = count_alive_neighbors(old_board, i, j);

            if (old_board[i][j].is_alive())
            {
                new_board[i][j].set_state(alive_neighbors == 2 || alive_neighbors == 3);
            }
            else
            {
                new_board[i][j].set_state(alive_neighbors == 3);
            }
        }
    }
}

void update_map(std::map<int, int>& map, std::vector<std::vector<Cell>>& board, int i)
{
    size_t w = board.size();
    size_t h = board[0].size();

    int alive_cells = 0;
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (board[i][j].is_alive())
                alive_cells++;
        }
    }
    map[i] = alive_cells;
}

void save_to_csv(const std::map<double, std::map<int, int>>& all_maps, int width, int height)
{
    std::ofstream file("all_simulations.csv", std::ios::out);
    file << "Iteration";

    for (const auto& prob_map : all_maps)
    {
        file << ",p(" << prob_map.first << ")";
    }
    file << "\n";

    for (int iteration = 0; iteration < 1000; ++iteration)
    {
        file << iteration;
        for (const auto& prob_map : all_maps)
        {
            if (prob_map.second.find(iteration) != prob_map.second.end())
            {
                double alive_ratio = static_cast<double>(prob_map.second.at(iteration)) / (width * height) * 100;
                file << "," << alive_ratio;
            }
            else
            {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}


void save_to_ppm(const std::vector<std::vector<Cell>>& board, int iteration, double prob)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << prob;
    std::string prob_str = ss.str();

    std::filesystem::create_directory("frames/p(" + prob_str + ")");

    std::string filename = "frames/p(" + prob_str + ")/frame_" + std::to_string(iteration) + ".ppm";
    std::ofstream file(filename, std::ios::binary);

    size_t width = board.size();
    size_t height = board[0].size();

    file << "P3\n" << width << " " << height << "\n255\n";

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (board[i][j].is_alive())
            {
                file << "0 0 0 ";
            }
            else
            {
                file << "255 255 255 ";
            }
        }
        file << "\n";
    }

    file.close();
}

void simulate_game(std::mt19937 gen, double prob, std::map<double, std::map<int, int >>& all_maps)
{
    int iteration = 0;
    int width = 100;
    int height = 100;

    std::vector<std::vector<Cell>> old_board = std::vector<std::vector<Cell>>(width, std::vector<Cell>(height, Cell(false)));
    std::vector<std::vector<Cell>> new_board = std::vector<std::vector<Cell>>(width, std::vector<Cell>(height, Cell(false)));

    std::map<int, int> map;

    randomize_board(old_board, gen, prob);

    while (iteration < 1000)
    {
        update_map(map, old_board, iteration);
        save_to_ppm(old_board, iteration, prob);
        update_board(old_board, new_board);
        old_board = new_board;
        iteration++;
    }

    prob = std::ceil(prob * 100.0) / 100.0;
    all_maps[prob] = map;
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::map<double, std::map<int, int>> all_maps;

    simulate_game(gen, 0.05, all_maps);
    simulate_game(gen, 0.1, all_maps);
    simulate_game(gen, 0.3, all_maps);
    simulate_game(gen, 0.6, all_maps);
    simulate_game(gen, 0.75, all_maps);
    simulate_game(gen, 0.8, all_maps);
    simulate_game(gen, 0.95, all_maps);

    save_to_csv(all_maps, 100, 100);
}
