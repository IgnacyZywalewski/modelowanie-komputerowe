#pragma once

double simulate_diffusion(bool eight_directions) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int steps_num = 1000;
    int walks_num = 10000;

    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    if (eight_directions) 
    {
        directions.insert(directions.end(), { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} });
    }

    std::uniform_int_distribution<> dist(0, directions.size() - 1);

    double total_r2 = 0.0;

    for (int w = 0; w < walks_num; ++w) 
    {
        int x = 0, y = 0;

        for (int s = 0; s < steps_num; ++s) 
        {
            auto [dx, dy] = directions[dist(gen)];
            x += dx;
            y += dy;
        }

        total_r2 += x * x + y * y;
    }

    double avg_r2 = total_r2 / walks_num;
    double D = avg_r2 / (4.0 * steps_num);

    return D;
}

void zadanie_5()
{
    double D_4 = simulate_diffusion(false);
    double D_8 = simulate_diffusion(true);
}

//Obliczone wspó³czynniki dyfuzji:
//- 4 kierunki - 0.248051 
//- 8 kierunków - 0.374462