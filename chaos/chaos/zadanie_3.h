#pragma once
#include <array>

void save_to_csv_3(std::vector<std::array<double, 3>> map)
{
	std::filesystem::create_directories("data/zadanie_3/");
	std::string filename = "data/zadanie_3/zadanie_3.csv";
	std::ofstream file(filename);

	file << "x,y,z\n";

	for (const auto& positions : map)
	{
		file << positions[0] << "," << positions[1] << "," << positions[2] << "\n";
	}
	file.close();
}

void zadanie_3()
{
	double delta = 10.0;
	double r = 28.0;
	double b = 8.0 / 3.0;
	double dt = 0.001;

	double x = 1.0, y = 1.0, z = 1.0;
	std::vector<std::array<double, 3>> positions;
	positions.push_back({ x, y, z });

	for (int i = 0; i < 150000; i++)
	{
		double dx = delta * (y - x);
		double dy = -x * z + r * x - y;
		double dz = x * y - b * z;

		x += dx * dt;
		y += dy * dt;
		z += dz * dt;

		positions.push_back({ x, y, z });
	}

	save_to_csv_3(positions);
}