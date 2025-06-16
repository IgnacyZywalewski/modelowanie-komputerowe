#pragma once
#include <vector>
#include <filesystem>
#include <map>
#include <fstream>

void save_to_csv_2(std::map<double, std::vector<double>> map)
{
	std::filesystem::create_directories("data/zadanie_2/");
	std::string filename = "data/zadanie_2/zadanie_2.csv";
	std::ofstream file(filename);

	file << "r,x\n";

	for (const auto& [r, x_values] : map)
	{
		for (const auto x : x_values)
		{
			file << r << "," << x<< "\n";
		}
	}

	file.close();
}

void zadanie_2()
{
	std::map<double, std::vector<double>> map;
	double x_prev = 0.5;

	for (double r = 2.4; r <= 4.0; r += 0.001)
	{
		std::vector<double> x_values;
		for (int i = 0; i < 200; i++)
		{
			double x_next = r * x_prev * (1 - x_prev);
			if (i > 100) x_values.push_back(x_next);
			x_prev = x_next;
		}
		map[r] = x_values;
	}
	save_to_csv_2(map);
}