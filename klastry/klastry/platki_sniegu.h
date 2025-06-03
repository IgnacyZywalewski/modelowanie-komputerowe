#pragma once

std::vector<std::pair<int, int>> hex_neighbors(int x, int y) {
	if (y % 2 == 0) {
		return {
			{x - 1, y}, {x + 1, y},
			{x, y - 1}, {x, y + 1},
			{x - 1, y - 1}, {x - 1, y + 1}
		};
	}
	else {
		return {
			{x - 1, y}, {x + 1, y},
			{x, y - 1}, {x, y + 1},
			{x + 1, y - 1}, {x + 1, y + 1}
		};
	}
}

int count_neighbors(const std::vector<std::vector<int>>& grid, int x, int y)
{
	auto neighbors = hex_neighbors(x, y);

	int count = 0;
	for (auto [nx, ny] : neighbors)
	{
		if (nx >= 0 && nx < grid.size() && ny >= 0 && ny < grid[0].size())
		{
			if (grid[nx][ny] == 1) count++;
		}
	}

	return count;
}


void save_to_ppm_2(std::vector<std::vector<int>> grid, int i, int n)
{
	std::filesystem::create_directories("frames/platki_sniegu/" + std::to_string(n));

	std::ostringstream oss;
	oss << "frames/platki_sniegu/" + std::to_string(n) + "/frame_" << std::setw(3) << std::setfill('0') << i << ".ppm";
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

void simulation(int n)
{
	int size = 300;
	int center = size / 2;
	int steps = 150;

	std::vector<std::vector<int>> grid(size, std::vector<int>(size, 0));

	switch (n) {
		case 1:
			grid[center][center] = 1;
			break;
		case 2:
			grid[center][center] = 1;
			grid[center + 1][center] = 1;
			grid[center][center + 1] = 1;
			break;
		default:
			grid[center][center] = 1;
			break;
	}

	std::vector<std::vector<int>> new_grid(size, std::vector<int>(size, 0));

	for (int i = 0; i < steps; i++)
	{
		save_to_ppm_2(grid, i, n);
		std::cout << "zapisano klastke: " << i << "\n";

		for (int j = 0; j < grid.size(); j++)
		{
			for (int k = 0; k < grid[0].size(); k++)
			{
				if (grid[j][k] == 1)
				{
					new_grid[j][k] = 1;
					continue;
				}

				if (n > 0)
				{
					if (count_neighbors(grid, j, k) == n)
					{
						new_grid[j][k] = 1;
					}
					else new_grid[j][k] = 0;
				}
				else
				{
					if (count_neighbors(grid, j, k) > n)
					{
						new_grid[j][k] = 1;
					}
					else new_grid[j][k] = 0;
				}
				
			}
		}
		grid = new_grid;
	}
}

void platki_sniegu()
{
	simulation(1);
	simulation(2);
	simulation(0);
}