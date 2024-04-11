#pragma once
#include "Game_Task.h"
#include <queue>
#include <thread>
#include <vector>
#include <condition_variable>
#include <mutex>


class TaskQueue
{
public:
	TaskQueue(int nof_threads) ;

	void addJob(Game_Task* task);

	void completeTask();

	~TaskQueue();

private:
	bool _exit = false;
	int _nof_threads;
	std::queue<Game_Task*> _tasks_queue;
	std::vector<std::thread> _threads;
	std::condition_variable _cv;
	std::mutex _mtx;	
};

