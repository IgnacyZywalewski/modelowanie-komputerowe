#pragma once

int simulate_walk_4_1D()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-1, 1);

	int steps_num = 1000;
	int starting_position = 0;
	int current_position = 0;
	int succes = 0;

	for (int j = 0; j < steps_num; j++)
	{
		int new_x = dist(gen);
		current_position += new_x;

		if (current_position == starting_position)
		{
			succes = 1;
			break;
		}
	}

	return succes;
}

int simulate_walk_4_2D()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-1, 1);

	int steps_num = 1000;
	int starting_position = 0;
	std::pair<int, int> current_position = { 0, 0 };
	int succes = 0;

	for (int j = 0; j < steps_num; j++)
	{
		int new_x = dist(gen);
		int new_y = dist(gen);

		current_position.first += new_x;
		current_position.second += new_y;

		if (current_position.first == 0 && current_position.second == 0)
		{
			succes = 1;
			break;
		}
	}

	return succes;
}

int simulate_walk_4_3D()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(-1, 1);

	int steps_num = 1000;
	int starting_position = 0;
	std::array<int, 3> current_position = { 0, 0, 0 };
	int succes = 0;

	for (int j = 0; j < steps_num; j++)
	{
		int new_x = dist(gen);
		int new_y = dist(gen);
		int new_z = dist(gen);

		current_position[0] += new_x;
		current_position[1] += new_y;
		current_position[2] += new_z;

		if (current_position[0] == 0 && current_position[1] == 0 && current_position[2] == 0)
		{
			succes = 1;
			break;
		}
	}

	return succes;
}


void zadanie_4()
{
	int succes_num_1D = 0;
	int succes_num_2D = 0;
	int succes_num_3D = 0;

	int walks_num = 1000;

	double probability_1D = 0.0;
	double probability_2D = 0.0;
	double probability_3D = 0.0;

	for (int i = 0; i < walks_num; i++)
	{
		succes_num_1D += simulate_walk_4_1D();
		succes_num_2D += simulate_walk_4_2D();
		succes_num_3D += simulate_walk_4_3D();
	}

	probability_1D = static_cast<double>(succes_num_1D) / static_cast<double>(walks_num);
	probability_2D = static_cast<double>(succes_num_2D) / static_cast<double>(walks_num);
	probability_3D = static_cast<double>(succes_num_3D) / static_cast<double>(walks_num);

	/*std::cout << "Prawdopodobienstwo dla d = 1 = " << probability_1D * 100 << "% \n" 
		<< "Prawdopodobienstwo dla d = 2 = " << probability_2D * 100 << "% \n"
		<< "Prawdopodobienstwo dla d = 3 = " << probability_3D * 100 << "% \n";*/


	/*Obliczone wartości prawdopodobieństwa:
	- d = 1 - 97.0%
	- d = 2 - 63.6%
	- d = 3 - 17.0%*/
}