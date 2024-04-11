#include <thread>
#include <mutex>
#include <iostream>

int account_1 = 1000;
int account_2 = 1000;

std::mutex m;

void unsafe_retrive(int amount, int n)
{
    for (int i = 0; i < n; i++)
    {
        account_1 -= amount;
    }
}

void unsafe_store(int amount, int n)
{
    for (int i = 0; i < n; i++)
    {
        account_1 += amount;
    }
}

// Mutex lock
void safe_retrive(int amount, int n)
{
    m.lock();
    for (int i = 0; i < n; i++)
    {
        account_2 -= amount;
    }
    m.unlock();
}

// Lock guard
void safe_store(int amount, int n)
{
    std::lock_guard<std::mutex> lock(m);
    for (int i = 0; i < n; i++)
    {
        account_2 += amount;
    }
}

int main()
{
    std::thread t1(unsafe_retrive, 10, 100000); // Nostetaan yth 1 000 0000
    std::thread t2(unsafe_store, 15, 100000);   // Talletetaan 1 500 000
                                                // Saldon pitäisi olla 1000 + 1500000 - 000000 = 501000

    std::thread t3(safe_retrive, 10, 100000);   // Nostetaan yth 1 000 0000
    std::thread t4(safe_store, 15, 100000);     // Talletetaan 1 500 000
                                                // Saldon pitäisi olla 1000 + 1500000 - 000000 = 501000

    t1.join();
    t2.join();
    t3.join();
    t4.join();


    std::cout << "No mutex saldo: " << account_1 << std::endl;;
    std::cout << "Mutex saldo: " << account_2 << std::endl;;
}
