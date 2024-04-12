// tehtava 8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>



class Ihminen
{
public:
	Ihminen(std::string name, int age) : _name(name), _age(age)
	{
	}
private:
	std::string _name;
	int _age;
};



template <class T>
class Log_Ptr
{
public:
	Log_Ptr(T* obj)
	{
		_obj = obj;
		std::cout << " objekti luotu: " << _obj;
	}

	~Log_Ptr()
	{
		std::cout << " objekti tuhottu: " << _obj;
		delete _obj;
	}


private:
	T* _obj;
};



int main()
{
	Ihminen* i = new Ihminen("Matti", 22);
	Log_Ptr<Ihminen> prt(i);
}

