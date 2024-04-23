#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

void spell_as_function(int& n)
{
    if (n - 100 < 0)
        n = 0;
    else
        n -= 100;
}

class spell_as_functor
{
public:
    void operator() (int& n)
    {
        if (n - 100 < 0)
            n = 0;
        else
            n -= 100;
    }
};

int main()
{
    std::vector<int> enemy_hp;
    std::srand(std::time(nullptr));
    for (int i = 0; i < 100; ++i)
    {
        enemy_hp.push_back(75 + rand() % 50);
    }

    std::vector<int> enemy_hp_1;
    std::vector<int> enemy_hp_2;
    std::vector<int> enemy_hp_3;

    enemy_hp_1 = enemy_hp;
    enemy_hp_2 = enemy_hp;
    enemy_hp_3 = enemy_hp;

    std::for_each(enemy_hp.begin(), enemy_hp.end(), spell_as_function);
    std::cout << "Casting Function Spell on all enemies..." << std::endl;
    for (int& i : enemy_hp)
        std::cout << "Function enemy HP: " << i << std::endl;

    std::for_each(enemy_hp_1.begin(), enemy_hp_1.end(), spell_as_functor());
    std::cout << "\n Casting Functor Spell on all enemies..." << std::endl;
    for (int& i : enemy_hp_1)
        std::cout << "Functor enemy HP: " << i << std::endl;

    std::cout << "\nCasting Lambda Spell on all enemies.." << std::endl;
    std::for_each(enemy_hp_2.begin(), enemy_hp_2.end(), [](int& n)
        {
            if (n - 100 < 0)
                n = 0;
            else
                n -= 100;
        });
    for(int& i : enemy_hp_2)
        std::cout << "Lambda enemy HP: " << i << std::endl;

    auto spell_as_lambda = [](int& n)
        {
            if (n - 100 < 0)
                n = 0;
            else
                n -= 100;
        };

    std::cout << "\nCasting Named Lambda Spell on all enemies..." << std::endl;
    std::for_each(enemy_hp_3.begin(), enemy_hp_3.end(), spell_as_lambda);
    for(int& i : enemy_hp_3)
        std::cout << "Named lambda enemy HP: " << i << std::endl;
}
