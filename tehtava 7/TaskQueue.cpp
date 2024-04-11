#include "TaskQueue.h"

TaskQueue::TaskQueue(int nof_threads)
{
	_nof_threads = nof_threads;
	for (int i = 0; i < _nof_threads; ++i)
	{
		_threads.push_back(std::thread(&TaskQueue::completeTask, this));
	}
}

TaskQueue::~TaskQueue()
{
	std::cout << "dst" << std::endl;

	while (!_tasks_queue.empty())
	{
		_cv.notify_one();
	}

	_exit = true;
	_cv.notify_all();
	for (int i = 0; i < _nof_threads; ++i) _threads[i].join();
	std::cout << "Joined threads" << std::endl;
}

void TaskQueue::addJob(Game_Task* task)
{
	std::unique_lock<std::mutex> lck(_mtx);
	std::cout << "pushed task" << std::endl;
	_tasks_queue.push(task);
	_cv.notify_one();
}

void TaskQueue::completeTask()
{
	std::unique_lock<std::mutex> lck(_mtx);
	std::cout << "Waiting" << std::endl;
	while (!_exit)
	{
		while (_tasks_queue.empty() && !_exit) _cv.wait(lck);
		if (_exit) return;
		std::cout << "complete task: " <<_tasks_queue.size() << std::endl;
		_tasks_queue.front()->perform();
		_tasks_queue.pop();
	}
}