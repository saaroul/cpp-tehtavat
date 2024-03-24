// tehtava 3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <thread>
#include <vector>
#include <iostream>
#include <chrono>

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
    }
   
};

class Physic_Task : public Game_Task
{
    void perform()
    {
        int x = 0;
        for (int i = 0; i < 4000000; i++)
            x++;
    }
};

class AI_Task : public Game_Task
{
    void perform()
    {
        int x = 0;
        for (int i = 0; i < 12000000; i++)
            x++;
    }
};

void call_tasks(std::vector<Game_Task*> tasks)
{
    size_t number_of_tasks = tasks.size();
    for (int i = 0; i < number_of_tasks; i++)
    {
        tasks[i]->perform();
    }
}


int main()
{
    std::vector<Game_Task*> tasks;
    
    for (int i = 0; i < 100; i++)
    {
        Game_Task* task = new Physic_Task();
        tasks.push_back(task);
    }
    for (int i = 0; i < 100; i++)
    {
        Game_Task* task = new Render_Task();
        tasks.push_back(task);
    }
    for (int i = 0; i < 100; i++)
    {
        Game_Task* task = new AI_Task();
        tasks.push_back(task);
    }

    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    const auto processor_count = std::thread::hardware_concurrency();

    int chunk_count = processor_count - 1;
    std::vector<std::vector<Game_Task*>> chunks(chunk_count);
    size_t chunk_size = tasks.size() / chunk_count + (tasks.size() % chunk_count != 0);

    std::vector<std::thread> threads;

    for (size_t i = 0; i < tasks.size(); i += chunk_size)
    {
        
        auto last = std::min(tasks.size(), i + chunk_size);
        auto index = i / chunk_size;
        auto& vec = chunks[index];
        vec.reserve(last - i);
        std::move(tasks.begin() + i, tasks.begin() + last, back_inserter(vec));
        threads.push_back(std::thread(call_tasks, vec));
    }
    
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i].join();
    }

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now();

    // Get duration. Substart timepoints to 
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken by function: "
        << duration.count() << " microseconds" << std::endl;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
