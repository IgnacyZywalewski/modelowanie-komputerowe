#pragma once
#include <random>
#include <map>
#include <fstream>
#include <filesystem>

void save_to_csv_1(std::map<int, int> map_1, std::map<int, int> map_2)
{
    std::filesystem::create_directory("dane");
    std::string filename = "dane/zadanie_1.csv";
    std::ofstream file(filename);

    file << "value,count_1,count_2\n";

    for (int i = 0; i <= 10000; i++)
    {
        file << i << "," << map_1[i] << "," << map_2[i] << "\n";
    }

    file.close();
}

std::map<int, int> mernenne_twister()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random(0, 10000);

    std::map<int, int> histogram;

    for (int i = 0; i < 100000; i++)
    {
        int r = random(gen);
        histogram[r]++;
    }

    return histogram;
}

std::map<int, int> modulo()
{
    std::map<int, int> histogram;
    srand(time(nullptr));

    for (int i = 0; i < 100000; i++)
    {
        int r = rand() % 10001;
        histogram[r]++;
    }

    return histogram;
}

void zadanie_1()
{
    std::map<int, int> histogram_1 = mernenne_twister();
    std::map<int, int> histogram_2 = modulo();
    save_to_csv_1(histogram_1, histogram_2);
}

//Wyniki uzyskane za pomoc¹ algortymu mernenne-twister s¹ lepsze, 
//poniewa¿ s¹ bardziej równomiernie roz³o¿one co oznacza ¿e wyniki s¹ bardziej losowe i mniej powtarzalne
//ni¿ te uzyskane za pomoc¹ funkcji rand()