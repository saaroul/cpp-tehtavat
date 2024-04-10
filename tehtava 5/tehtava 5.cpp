#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <chrono>

int main()
{
    int n = 1000000;
    std::vector<int> nums, seq_nums, par_nums, par_unseq_nums;
    
    // Populate lists
    nums.reserve(n);
    for (int i = 0; i < n; i++)
    {
        nums.push_back(i);
    }

    // Copies for different policies
    seq_nums = nums;
    par_nums = nums;
    par_unseq_nums = nums;
    
    // No policy stated
    auto start = std::chrono::high_resolution_clock::now();

    std::for_each(nums.begin(), nums.end(), [](int& n) {n++; });

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "No policy: " << duration << std::endl;


    // Explicit sequential policy
    start = std::chrono::high_resolution_clock::now();

    std::for_each(std::execution::seq, seq_nums.begin(), seq_nums.end(), [](int& n) {n++; });

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Sequential policy: " << duration << std::endl;


    // Parallel policy
    start = std::chrono::high_resolution_clock::now();

    std::for_each(std::execution::par, par_nums.begin(), par_nums.end(), [](int& n) {n++; });

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Parallel policy: " << duration << std::endl;


    // Parallel unsequential policy
    start = std::chrono::high_resolution_clock::now();

    std::for_each(std::execution::par_unseq, par_unseq_nums.begin(), par_unseq_nums.end(), [](int& n) {n++; });

    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Parallel unsequenced policy: " << duration << std::endl;

}
