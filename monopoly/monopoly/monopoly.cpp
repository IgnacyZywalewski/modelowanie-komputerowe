#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <fstream>

struct Game_data
{
    int n = 0;
    int dices = 2;
    int dice_1 = 0;
    int dice_2 = 0;
    int fields_num = 40;
    bool prison = false;
    int prison_filed = 30;
    int prison_punishment = 20;

    std::map<int, int> probability_1;
    std::map<int, int> probability_2;
    std::map<int, int> probability_3;
    std::map<int, int> probability_4;
};

struct Player
{
    void set_position(int new_pos) { position = new_pos; }
    int get_position() { return position; }
    void reset_position() { position = 0; }

private:
    int position = 0;
};

int dice_roll(std::mt19937& gen)
{
    std::uniform_int_distribution<> distr(1, 6);
    return distr(gen);
}

void simulate_game(Game_data& game, Player& player, std::mt19937& gen, std::map<int, int>& probability_map)
{
    for (int i = 1; i <= game.n; i++)
    {
        game.dice_1 = dice_roll(gen);
        game.dice_2 = dice_roll(gen);
        player.set_position(player.get_position() + game.dice_1 + game.dice_2);

        if (player.get_position() > game.fields_num)
        {
            player.set_position(player.get_position() - game.fields_num);
        }

        probability_map[player.get_position()]++;

        if (game.prison && player.get_position() == game.prison_filed)
        {
            player.set_position(player.get_position() - game.prison_punishment);
            probability_map[player.get_position()]++;
        }
    }
}

void save_to_csv(const Game_data& game, const std::string& filename = "prawdopodobienstwo.csv")
{
    std::ofstream file(filename);

    file << "Field,1,2,3,4\n";

    for (int i = 1; i <= game.fields_num; i++)
    {
        double p1 = (game.probability_1.count(i) ? (static_cast<double>(game.probability_1.at(i)) / 100 ) * 100 : 0);
        double p2 = (game.probability_2.count(i) ? (static_cast<double>(game.probability_2.at(i)) / 100 ) * 100 : 0);
        double p3 = (game.probability_3.count(i) ? (static_cast<double>(game.probability_3.at(i)) / 1000000) * 100 : 0);
        double p4 = (game.probability_4.count(i) ? (static_cast<double>(game.probability_4.at(i)) / 1000000) * 100 : 0);

        file << i << "," << p1 << "," << p2 << "," << p3 << "," << p4 << "\n";
    }

    file.close();
}

int main()
{
    Game_data game;
    Player player;

    std::random_device rd;
    std::mt19937 gen(rd());

    // n = 100, bez więzienia
    game.n = 100;
    game.prison = false;
    simulate_game(game, player, gen, game.probability_1);
    player.reset_position();

    // n = 100, z więzieniem
    game.prison = true;
    simulate_game(game, player, gen, game.probability_2);
    player.reset_position();

    // n = 1 000 000, bez więzienia
    game.n = 1000000;
    game.prison = false;
    simulate_game(game, player, gen, game.probability_3);
    player.reset_position();

    // n = 1 000 000, z więzieniem
    game.prison = true;
    simulate_game(game, player, gen, game.probability_4);
    player.reset_position();

    save_to_csv(game);

    std::cout << "Dane zostaly zapisane do prawdopodobienstwo.csv\n";
}
