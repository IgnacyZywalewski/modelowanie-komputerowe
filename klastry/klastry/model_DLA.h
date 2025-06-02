#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <filesystem>
#include <string>
#include <cmath>
#include <set>

std::pair<int, int> random_direction() 
{
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0} };

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dir(0, directions.size() - 1);
    int idx = dir(gen);

    return directions[idx];
}

int distance(std::vector<std::vector<int>> grid, int x, int y)
{
    return std::sqrt((x - grid.size() / 2) * (x - grid.size() / 2) + (y - grid.size() / 2) * (y - grid.size() / 2));
}

bool is_adjacent(const std::vector<std::vector<int>>& grid, int x, int y) 
{
    return grid[x + 1][y] || grid[x - 1][y] || grid[x][y + 1] || grid[x][y - 1];
}

void save_final_image(const std::vector<std::vector<int>>& grid) 
{
    std::filesystem::create_directories("frames/DLA");
    std::ofstream file("frames/DLA/model_DLA.ppm");
    file << "P3\n" << grid.size() << " " << grid.size() << "\n255\n";

    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid.size(); x++)
        {
            if (grid[x][y] == 1)
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


void model_DLA()
{
    int size = 400;
    int center = size / 2;
    int particles = 5000;

    std::vector<std::vector<int>> grid(size, std::vector<int>(size, 0));
    grid[center][center] = 1;

    std::filesystem::create_directories("data");
    std::ofstream csv("data/radius_DLA.csv");
    csv << "particles,radius\n";

    int max_radius = 0;

    for (int p = 1; p <= particles; p++)
    {
        std::cout << p << "\n";

        double angle = 2 * 3.14 * ((double)rand() / RAND_MAX);
        int r = max_radius + 5;
        int x = center + int(r * cos(angle));
        int y = center + int(r * sin(angle));

        while (true) 
        {
            auto [dx, dy] = random_direction();
            x += dx;
            y += dy;

            if (x <= 1 || x >= size - 2 || y <= 1 || y >= size - 2) break;

            if (is_adjacent(grid, x, y)) 
            {
                grid[x][y] = 1;
                int d = distance(grid, x, y);
                if (d > max_radius) max_radius = d;
                break;
            }

            if (distance(grid, x, y) > max_radius + 10) break;
        }

        if (p % 50 == 0) csv << p << "," << max_radius << "\n";
    }

    csv.close();
    save_final_image(grid);
}
