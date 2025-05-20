#pragma once

//2D
void save_to_csv_2D(const std::map<int, std::map<int, std::pair<int, int>>>& all_walks)
{
	std::filesystem::create_directory("dane");
	std::ofstream file("dane/zadanie_2_2D.csv");

	file << "step";
	for (int i = 0; i < all_walks.size(); i++)
	{
		file << ",walk_" << i + 1 << "_x,walk_" << i + 1 << "_y";
	}
	file << "\n";

	size_t steps = all_walks.begin()->second.size();

	for (int step = 0; step < steps; step++)
	{
		file << step;
		for (int walk = 0; walk < all_walks.size(); walk++)
		{
			auto pos = all_walks.at(walk).at(step);
			file << "," << pos.first << "," << pos.second;
		}
		file << "\n";
	}

	file.close();
}

std::map<int, std::pair<int, int>> simulate_walk_2_2D()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-1, 1);

	std::pair<int, int> current_position = { 0, 0 };
	std::map<int, std::pair<int, int>> position_map;

	int steps_num = 1000;

	for (int i = 0; i <= steps_num; i++)
	{
		position_map[i] = current_position;

		int new_x = dist(gen);
		int new_y = dist(gen);

		current_position.first += new_x;
		current_position.second += new_y;
	}

	return position_map;
}

void zadanie_2_2D()
{
	std::map<int, std::map<int, std::pair<int, int>>> all_walks;
	int walks_num = 10;

	for (int i = 0; i < walks_num; i++)
	{
		all_walks[i] = simulate_walk_2_2D();
	}

	save_to_csv_2D(all_walks);
}



//3D
void save_to_csv_3D(const std::map<int, std::map<int, std::array<int, 3>>>& all_walks)
{
	std::filesystem::create_directory("dane");
	std::ofstream file("dane/zadanie_2_3D.csv");

	file << "step";
	for (int i = 0; i < all_walks.size(); i++)
	{
		file << ",walk_" << i + 1 << "_x,walk_" << i + 1 << "_y,walk_" << i + 1 << "_z";
	}
	file << "\n";

	size_t steps = all_walks.begin()->second.size();

	for (int step = 0; step < steps; step++)
	{
		file << step;
		for (int walk = 0; walk < all_walks.size(); walk++)
		{
			auto pos = all_walks.at(walk).at(step);
			file << "," << pos[0] << "," << pos[1] << "," << pos[2];
		}
		file << "\n";
	}

	file.close();
}

std::map<int, std::array<int, 3>> simulate_walk_2_3D()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-1, 1);

	std::array<int, 3> current_position = { 0, 0, 0 };
	std::map<int, std::array<int, 3>> position_map;

	int steps_num = 1000;

	for (int i = 0; i <= steps_num; i++)
	{
		position_map[i] = current_position;

		int new_x = dist(gen);
		int new_y = dist(gen);
		int new_z = dist(gen);

		current_position[0] += new_x;
		current_position[1] += new_y;
		current_position[2] += new_z;

	}

	return position_map;
}

void zadanie_2_3D()
{
	std::map<int, std::map<int, std::array<int, 3>>> all_walks;
	int walks_num = 10;

	for (int i = 0; i < walks_num; i++)
	{
		all_walks[i] = simulate_walk_2_3D();
	}

	save_to_csv_3D(all_walks);
}

void zadanie_2()
{
	zadanie_2_2D();
	zadanie_2_3D();
}