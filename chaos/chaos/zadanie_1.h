#pragma once
#include <map>
#include <fstream>
#include <filesystem>

void save_to_csv_1(std::map<double, double> distance_map)
{
	std::filesystem::create_directories("data/zadanie_1/");
	std::string filename = "data/zadanie_1/zadanie_1.csv";
	std::ofstream file(filename);

	file << "dist,sum_dist\n";

	for (const auto& [distance, sum_distance] : distance_map)
	{
		file << distance << "," << sum_distance << "\n";
	}

	file.close();
}

double simulate_chaos(double a, double b, double distance)
{
	a += distance;

	double lambda = 1.999;
	double sum_a = 0.0;
	double sum_b = 0.0;

	for (int i = 0; i < 1000; i++)
	{
		a *= lambda;
		b *= lambda;

		if (a > 1.0) a -= 1.0;
		if (b > 1.0) b -= 1.0;

		sum_a += a;
		sum_b += b;
	}

	return sum_a - sum_b;
}

void zadanie_1()
{
	double a = 0.5430000;
	double b = 0.5430000;

	std::map<double, double> distance_map;
	double start_distance = 0.0;

	for (int i = 0; i < 1000; i++)
	{
		double sum_distance = simulate_chaos(a, b, start_distance);
		distance_map[start_distance] = sum_distance;
		start_distance += 0.0000001;
	}

	save_to_csv_1(distance_map);
}