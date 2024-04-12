
#include <ctime>
#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>




template <class T>
class Log_Ptr
{
public:
	Log_Ptr(T* obj)
	{
		std::cout << " objekti luotu: " << _obj;
		_obj = obj;
	}

	~Log_Ptr()
	{
		std::cout << " objekti tuhottu: " << _obj;
		delete _obj;
	}


private:
	T* _obj;
};

