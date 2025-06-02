#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <filesystem>
#include <string>
#include <iomanip>

std::vector<std::pair<int, int>> get_free_neighbors(const std::vector<std::vector<int>>& grid, int x, int y) {
	std::vector<std::pair<int, int>> result;
	std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	for (auto [dx, dy] : directions)
	{
		int nx = x + dx;
		int ny = y + dy;

		if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] == 0)
		{
			result.push_back({ nx, ny });
		}
	}
	return result;
}

bool has_free_neighbors(const std::vector<std::vector<int>>& grid, int x, int y)
{
	std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

	for (auto [dx, dy] : directions)
	{
		int nx = x + dx;
		int ny = y + dy;

		if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size() && grid[nx][ny] == 0)
		{
			return true;
		}
	}
	return false;
}

void save_to_ppm(std::vector<std::vector<int>> grid, int i)
{
	std::filesystem::create_directories("frames/eden");

	std::ostringstream oss;
	oss << "frames/eden/frame_" << std::setw(3) << std::setfill('0') << i << ".ppm";
	std::string filename = oss.str();

	std::ofstream file(filename, std::ios::binary);

	size_t width = grid.size();
	size_t height = grid[0].size();

	file << "P3\n" << width << " " << height << "\n255\n";

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (grid[i][j] == 1)
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

double calculate_radius(std::vector<std::vector<int>> grid)
{
	double radius = 0.0;
	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[0].size(); y++)
		{
			if (grid[x][y] == 1)
			{
				double dist = std::sqrt((x - grid.size() / 2) * (x - grid.size() / 2) + (y - grid[0].size() / 2) * (y - grid[0].size() / 2));

				if (dist > radius)
				{
					radius = dist;
				}
			}
		}
	}
	return radius;
}

void save_to_csv(std::vector<std::pair<int, int>> radius_vector)
{
	std::filesystem::create_directories("data");
	std::string filename = "data/radius_eden.csv";
	std::ofstream file(filename);

	file << "step,radius\n";

	for (const auto& [step, radius] : radius_vector)
	{
		file << step << "," << radius << "\n";
	}

	file.close();
}

void model_edena()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	int width = 100;
	int height = 100;
	int steps = 1000;

	std::vector<std::vector<int>> grid(width, std::vector<int>(height, 0));
	int x = width / 2;
	int y = height / 2;
	grid[x][y] = 1;

	std::vector<std::pair<int, int>> active_cells;
	active_cells.push_back({ x, y });

	std::vector<std::pair<int, int>> radius_vector;

	for (int i = 0; i <= steps; i++)
	{
		save_to_ppm(grid, i);

		std::cout << "zapisano klatke: " << i << "\n";

		bool grown = false;

		while (!grown)
		{
			std::uniform_int_distribution<int> random_cell(0, active_cells.size() - 1);
			int idx = random_cell(gen);
			std::pair<int, int> active_cell = active_cells[idx];
			int ax = active_cell.first;
			int ay = active_cell.second;

			std::vector<std::pair<int, int>> neighbors = get_free_neighbors(grid, ax, ay);

			if (!neighbors.empty())
			{
				std::uniform_int_distribution<int> random_neighbor(0, neighbors.size() - 1);
				int idx = random_neighbor(gen);
				std::pair<int, int> neighbor = neighbors[idx];

				int nx = neighbor.first;
				int ny = neighbor.second;

				grid[nx][ny] = 1;
				grown = true;

				if (has_free_neighbors(grid, nx, ny))
				{
					active_cells.push_back({ nx, ny });
				}
			}

			else {
				active_cells.erase(active_cells.begin() + idx);
				if (active_cells.empty()) break;
			}
		}

		if (i % 100 == 0)
		{
			double r = calculate_radius(grid);
			radius_vector.push_back({ i, r });
		}
	}
	save_to_csv(radius_vector);
}
