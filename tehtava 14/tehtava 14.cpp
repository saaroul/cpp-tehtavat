#include <iostream>

class BigData
{
public:
    BigData(int size)
    {
        _size = size;
        _buf = (char*)malloc(_size);
    }

    // 14
    BigData(BigData& data)
    {
        _size = data._size;
        _buf = (char*)malloc(_size);
        memcpy(_buf, data._buf, data._size);

    }

    BigData& operator=(const BigData& data)
    {
        if (this != &data)
        {
            free(_buf);
            _size = data._size;
            _buf = (char*)malloc(_size);
            memcpy(_buf, data._buf, data._size);
        }
        
        return *this;
    }

    // 15
    BigData(BigData&& data)
    {
        _size = data._size;
        _buf = data._buf;
        data._buf = nullptr;

    }
    BigData& operator=(BigData&& data)
    {
        _size = data._size;
        _buf = data._buf;
        data._buf = nullptr;

        return *this;
    }

    ~BigData()
    {
        free(_buf);
    }

private:
    size_t _size;
    char* _buf;
};

int main()
{
    BigData a(1024);
    BigData b(2048);
    a = a;
    a = b;
    BigData c(a);

    BigData a2(BigData(1024));
    BigData b2(1024);
    b2 = BigData(1024);
    BigData c2(std::move(a2));
}
