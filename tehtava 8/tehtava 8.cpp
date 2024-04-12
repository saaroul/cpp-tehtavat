// tehtava 8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <chrono>
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

std::string timestamp()
{
	auto start = std::chrono::system_clock::now();
	auto legacyStart = std::chrono::system_clock::to_time_t(start);
	char tmBuff[30];
	ctime_s(tmBuff, sizeof(tmBuff), &legacyStart);
	
	std::string s(tmBuff);

	if (!s.empty() && s[s.length() - 1] == '\n') 
	{
		s.erase(s.length() - 1);
	}

	s = "[" + s + "]";

	return s;
}


class Ihminen
{
public:
	Ihminen(std::string name, int age) : _name(name), _age(age)
	{
	}
	void tervehdi()
	{
		std::cout << "Hei olen " << _name << std::endl;
	}
private:
	std::string _name;
	int _age;
};



template <typename T>
class Log_Ptr
{
public:
	Log_Ptr() : _obj(0), _ref_count(0)
	{
		_ref_count = new Ref_Count();
		_ref_count->addRef();
	}
	Log_Ptr(T* obj)
	{
		_ref_count = new Ref_Count();
		_ref_count->addRef();
		_obj = obj;
		log_op("omistajuus siirretty");
	}

	Log_Ptr(const Log_Ptr<T>& log_ptr) : _obj(log_ptr._obj), _ref_count(log_ptr._ref_count)
	{
		log_op("copy const");
		_ref_count->addRef();
	}

	~Log_Ptr()
	{
		if (_ref_count->release() == 0)
		{
			log_op("olio tuhottu");
			delete _obj;
			delete _ref_count;
		}
	}

	T* operator-> ()
	{
		log_op("operator->");
		return _obj;
	}

	T& operator* ()
	{
		log_op("operator*");
		return *_obj;
	}

	Log_Ptr<T>& operator= (const Log_Ptr<T>& log_ptr) 
	{
		if (this != &log_ptr)
		{
			if (_ref_count->release() == 0)
			{
				log_op("operator= vanha olio tuhottu");
				delete _obj;
				delete _ref_count;
			}
			_obj = log_ptr._obj;
			_ref_count = log_ptr._ref_count;
			_ref_count->addRef();
			log_op("operator=");
		}
		return *this;
	}

private:
	class Ref_Count
	{
	public:
		Ref_Count() { _count = 0; }

		void addRef()
		{
			_count++;
		}

		int release()
		{
			return --_count;
		}

	private:
		int _count;
	};

	T* _obj;
	Ref_Count* _ref_count;

	void log_op(std::string msg)
	{
		msg = " " + msg + " ";
		std::cout << timestamp() << msg << "(address: " << _obj << ")" << std::endl;

	}
	
};



int main()
{
	Log_Ptr<Ihminen> p(new Ihminen("Matti", 22));
	p->tervehdi();
	{
		Log_Ptr<Ihminen> q = p;
		q->tervehdi();

		Log_Ptr<Ihminen> r;
		r = p;
		r->tervehdi();
	}
	p->tervehdi();	
}

