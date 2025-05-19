#pragma once
#include <random>
#include <map>
#include <fstream>
#include <filesystem>

void save_to_csv_3(std::map<int, int> map)
{
	std::filesystem::create_directory("dane");
	std::ofstream file("dane/zadanie_3.csv");

	file << "position,value\n";
	for (auto [key, value]: map)
	{
		file << key << "," << value << "\n";
	}
	file.close();
}

int simulate_walk()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-1, 1);

	int steps_num = 1000;
	int current_position = 0;
	for (int j = 0; j < steps_num; j++)
	{
		int new_x = dist(gen);
		current_position += new_x;
	}
	
	return current_position;
}

void zadanie_3()
{
	int walks_num = 10000;
	std::map<int, int> position_map;

	for (int i = 0; i < walks_num; i++)
	{
		int end_position = simulate_walk();
		position_map[end_position]++;
	}

	save_to_csv_3(position_map);
}


//Bardziej prawdopodobne jest to, ¿e dziecko znajdzie siê w odlegoœci 1 ni¿ 30 od punktu startowego 