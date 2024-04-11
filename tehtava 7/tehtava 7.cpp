#include <queue>
#include <future>
#include <thread>
#include <iostream>
#include "TaskQueue.h"
#include <chrono>

int main()
{
    TaskQueue task_queue(5);

    for (int i = 0; i < 100; i++)
    {
        Game_Task* task = new Physic_Task();
        task_queue.addJob(task);
    }
    for (int i = 0; i < 100; i++)
    {
        Game_Task* task = new Render_Task();
        task_queue.addJob(task);
    }
    for (int i = 0; i < 100; i++)
    {
        Game_Task* task = new AI_Task();
        task_queue.addJob(task);
    }

    std::cout << "main finished" << std::endl;

    return 0;
}

