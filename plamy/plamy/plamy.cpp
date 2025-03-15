#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <thread> 
#include <chrono>
#include <map>
#include <fstream>
#include <filesystem>

struct Cell
{
    Cell(bool alive) : alive(alive) {}

    bool is_alive() const { return alive; }
    void set_state(bool new_state) { alive = new_state; }

private:
    bool alive;
};

void set_board(std::vector<std::vector<Cell>>& board, int h, int w)
{
    board = std::vector<std::vector<Cell>>(w, std::vector<Cell>(h, Cell(false)));
}

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
                alive_neighbors++;
            }

            if (alive_neighbors == 4 || alive_neighbors == 6 || alive_neighbors == 7 || alive_neighbors == 8 || alive_neighbors == 9)
            {
                new_board[i][j].set_state(true);
            }
            else
            {
                new_board[i][j].set_state(false);
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
            {
                alive_cells++;
            }
        }
    }
    map[i] = alive_cells;
}

void save_to_csv(std::map<int, int> map, int width, int height)
{
    std::ofstream file("gestosc.csv");
    file << "Iteration,AliveRatio\n";
    for (auto i : map)
    {
        file << i.first << "," << static_cast<double>(i.second) / (width * height) << "\n";
    }
    file.close();
}


void save_to_ppm(const std::vector<std::vector<Cell>>& board, int iteration)
{
    std::filesystem::create_directory("frames");

    std::string filename = "frames/frame_" + std::to_string(iteration) + ".ppm";
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

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    double prob = 0.5;

    int width = 1000;
    int height = 1000;

    std::vector<std::vector<Cell>> old_board;
    std::vector<std::vector<Cell>> new_board;

    std::map<int, int> map;
    int iteration = 0;
    int max_iteration = 100;
    
    set_board(old_board, width, height);
    set_board(new_board, width, height);

    randomize_board(old_board, gen, prob);

    while (iteration < max_iteration)
    {
        update_map(map, old_board, iteration);
        save_to_ppm(old_board, iteration);
        update_board(old_board, new_board);

        old_board = new_board;
        iteration++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    save_to_csv(map, width, height);
}
