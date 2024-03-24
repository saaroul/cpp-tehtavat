#include <vector>
#include <iostream>
#include <thread>

void sum(std::vector<int>::iterator itr, int chunk_size, int& sum)
{
	for (int i = 0; i < chunk_size; i++)
	{
		sum += *itr;
	}
	std::cout << sum << std::endl;
}

int main() {
	// Main

	std::vector<int> nums(100000, 2);
	int chunk_size = nums.size() / 4;

	int sum1 = 0;
	int sum2 = 0;
	int sum3 = 0;
	int sum4 = 0;

	std::thread t1(sum, nums.begin(), chunk_size, std::ref(sum1));
	std::thread t2(sum, nums.begin() + chunk_size, chunk_size, std::ref(sum2));
	std::thread t3(sum, nums.begin() + chunk_size * 2, chunk_size, std::ref(sum3));
	std::thread t4(sum, nums.begin() + chunk_size * 3, chunk_size, std::ref(sum4));

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	int total = sum1 + sum2 + sum3 + sum4;

	std::cout << total;


	return 0;
}