#include <iostream>
#include <future>
#include <chrono>

using Iter = std::vector<int>::iterator;

int sum(Iter beg, Iter end)
{
	int sum = 0;
	for (Iter it = beg; it != end; ++it)
	{
		sum += *it;
	}
	return sum;
}

int main()
{
	int chunk_count = 8;
	std::vector<int> nums(1020503254, 5);
	int chunk_size = nums.size() / chunk_count + (nums.size() % chunk_count != 0);

	// Get starting timepoint
	auto start = std::chrono::high_resolution_clock::now();

	std::vector<std::future<int>> futs;

	for (int i = 0; i < chunk_count; i++)
	{
		Iter start = nums.begin() + i * chunk_size;
		Iter end;
		if (i * chunk_size + chunk_size > nums.size())
		{
			end = nums.end();
		}
		else
		{
			end = nums.begin() + i * chunk_size + chunk_size;
		}
		
		futs.push_back(std::async(sum, start, end));
	}

	int async_total = 0;
	for (auto& fut : futs)
	{
		int ret = fut.get();
		async_total += ret;
	}

	// Get ending timepoint
	auto stop = std::chrono::high_resolution_clock::now();

	// Get duration. Substart timepoints to 
	// get duration. To cast it to proper unit
	// use duration cast method
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Time taken by async sum: "
		<< duration.count() << " microseconds" << std::endl;

	std::cout << "Async Total: " << async_total << std::endl;

	start = std::chrono::high_resolution_clock::now();

	int sync_total = 0;
	for (int num : nums)
	{
		sync_total += num;
	}

	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	std::cout << "Time taken by sync sum: "
		<< duration.count() << " microseconds" << std::endl;

	std::cout << "Sync Total: " << sync_total;
}
