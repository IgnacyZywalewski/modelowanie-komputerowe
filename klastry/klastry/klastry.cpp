#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <filesystem>
#include <string>
#include <iomanip>

void choose_new_cell(std::vector<std::vector<int>> old_grid, std::vector<std::vector<int>>& new_grid, int x, int y)
{
	std::vector<std::pair<int, int>> positions;
	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			if (i == 0 && j == 0) continue;

			int dx = i + x;
			int dy = j + y;

			if (dx >= 0 && dx < old_grid.size() && dy >= 0 && dy < old_grid[0].size())
			{
				if (old_grid[dx][dy] == 0) positions.push_back({ dx, dy });
			}
		}
	}

	if (positions.size() != 0)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> random(0, positions.size() - 1);
		int r = random(gen);

		new_grid[positions[r].first][positions[r].second] = 1;
	}
}

void save_to_ppm(std::vector<std::vector<int>> grid, int i)
{
	std::filesystem::create_directory("frames");

	std::ostringstream oss;
	oss << "frames/frame_" << std::setw(3) << std::setfill('0') << i << ".ppm";
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


void eden_model()
{
	int width = 100;
	int heigth = 100;
	int steps = 100;

	std::vector<std::vector<int>> old_grid(width, std::vector<int>(heigth, 0));
	std::vector<std::vector<int>> new_grid(width, std::vector<int>(heigth, 0));

	old_grid[50][50] = 1;

	for (int i = 0; i < steps; i++)
	{
		save_to_ppm(old_grid, i);
		std::cout << "zapisano klatke: " << i << "\n";

		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < heigth; k++)
			{
				if (old_grid[j][k] == 1)
				{
					new_grid[j][k] = 1;
					choose_new_cell(old_grid, new_grid, j, k);
				}
			}
		}
		old_grid = new_grid;
	}
}


int main()
{
	eden_model();
}