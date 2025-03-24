#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <array>
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