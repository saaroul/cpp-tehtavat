#pragma once
#include <iostream>

class Game_Task
{
public:
    virtual void perform() = 0;
};

class Render_Task : public Game_Task
{
    void perform()
    {
        int x = 0;
        for (int i = 0; i < 8000000; i++)
            x++;
    std::cout << "render task completed" << std::endl;
    }
};

class Physic_Task : public Game_Task
{
    void perform()
    {
        int x = 0;
        for (int i = 0; i < 4000000; i++)
            x++;
    std::cout << "physic task completed" << std::endl;
    }

};

class AI_Task : public Game_Task
{
    void perform()
    {
        int x = 0;
        for (int i = 0; i < 12000000; i++)
            x++;
    std::cout << "ai task completed" << std::endl;
    }

};

