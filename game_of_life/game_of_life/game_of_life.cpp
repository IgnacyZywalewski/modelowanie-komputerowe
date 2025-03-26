#include "game_of_life.h"

//Zadanie 2
void save_to_csv(const std::map<double, std::map<int, int>>& all_maps, int width, int height)
{
    std::ofstream file("all_simulations.csv", std::ios::out);
    file << "Iteration";

    for (const auto& prob_map : all_maps)
    {
        file << ",p(" << prob_map.first << ")";
    }
    file << "\n";

    for (int iteration = 0; iteration < 1000; ++iteration)
    {
        file << iteration;
        for (const auto& prob_map : all_maps)
        {
            if (prob_map.second.find(iteration) != prob_map.second.end())
            {
                double alive_ratio = static_cast<double>(prob_map.second.at(iteration)) / (width * height) * 100;
                file << "," << alive_ratio;
            }
            else
            {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}


void save_to_ppm(const std::vector<std::vector<Cell>>& board, int iteration, double prob)
{
    std::stringstream ss;
    ss << std::defaultfloat << prob;
    std::string prob_str = ss.str();

    std::filesystem::create_directory("frames/p(" + prob_str + ")");

    std::string filename = "frames/p(" + prob_str + ")/frame_" + std::to_string(iteration) + ".ppm";
    std::ofstream file(filename, std::ios::binary);

    size_t width = board.size();
    size_t height = board[0].size();

    file << "P3\n" << width << " " << height << "\n255\n";

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (board[i][j].is_alive())
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

void simulate_game(std::mt19937 gen, double prob, std::map<double, std::map<int, int >>& all_maps, int w, int h)
{
    int iteration = 0;

    std::vector<std::vector<Cell>> old_board(w, std::vector<Cell>(h, Cell(false)));
    std::vector<std::vector<Cell>> new_board(w, std::vector<Cell>(h, Cell(false)));

    std::map<int, int> map;

    randomize_board(old_board, gen, prob);

    while (iteration < 1000)
    {
        update_map(map, old_board, iteration);
        save_to_ppm(old_board, iteration, prob);
        update_board(old_board, new_board);
        old_board = new_board;
        iteration++;
    }
    all_maps[prob] = map;
}


//Zadanie 3
std::vector<double> calculate_density(std::mt19937& gen, double prob, int size, int Tmax, int N)
{
    std::vector<double> densities;

    for (int n = 0; n < N; n++)
    {
        std::vector<std::vector<Cell>> board(size, std::vector<Cell>(size, Cell(false)));
        std::vector<std::vector<Cell>> new_board(size, std::vector<Cell>(size, Cell(false)));

        randomize_board(board, gen, prob);

        double total_density = 0.0;

        for (int t = 0; t < Tmax; t++)
        {            
            int alive_cells = 0;
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    alive_cells = count_alive_neighbors(board, i, j);
                }
            }

            double density = static_cast<double>(alive_cells) / (size * size);
            total_density += density;

            update_board(board, new_board);
            board = new_board;
        }
        densities.push_back(total_density / Tmax);
    }
    return densities;
}

double mean(const std::vector<double>& values)
{
    double sum = 0.0;
    for (double v : values)
        sum += v;
    return sum / values.size();
}

double standard_error(const std::vector<double>& values)
{
    double avg = mean(values);
    double sum = 0.0;

    for (double v : values)
        sum += (v - avg) * (v - avg);

    return sqrt(sum / (values.size() - 1)) / sqrt(values.size());
}


int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    //Zadanie 2
    int width = 100;
    int height = 100;
    std::map<double, std::map<int, int>> all_maps;

    simulate_game(gen, 0.05, all_maps, width, height);
    simulate_game(gen, 0.1, all_maps, width, height);
    simulate_game(gen, 0.3, all_maps, width, height);
    simulate_game(gen, 0.6, all_maps, width, height);
    simulate_game(gen, 0.75, all_maps, width, height);
    simulate_game(gen, 0.8, all_maps, width, height);
    simulate_game(gen, 0.95, all_maps, width, height);
    
    save_to_csv(all_maps, 100, 100);
    

    //Zadanie 3
    std::array<int, 5> L_values = { 10, 100, 200, 500, 1000 };
    double prob = 0.5;
    int Tmax = 1000;
    int N = 100;

    std::ofstream file("standard_error.csv");
    file << "L,StandardError\n";

    for (int L : L_values)
    {
        std::vector<double> densities = calculate_density(gen, prob, L, Tmax, N);
        double avg_density = mean(densities);
        double error = standard_error(densities);

        std::cout << "L = " << L << ", Mean Density = " << avg_density << ", Standard Error = " << error << "\n";
        file << L << "," << error << "\n";
    }

    file.close();
}