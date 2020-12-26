// Netetskaya_lab_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <algorithm>
#include <mutex>
#include <vector>
#include <atomic>
#include <array>
#include "windows.h"
#include <thread>

static const int NumTasks = 1024 * 1024;
static const std::vector<int>  NumThreads = { 4, 8, 16, 32 };
static const int sleep = 10;
unsigned int main_counter_mutex = 0;
unsigned int main_counter_atomic = 0;
std::mutex _mutex;

void mutex_method(int* arr, bool is_sleep) {
    unsigned int counter = 0;
    while (true)
    {
        _mutex.lock();
        counter = main_counter_mutex++;
        _mutex.unlock();
        if (counter < NumTasks)
        {
            arr[counter]++;

            if (is_sleep)
            {
                std::this_thread::sleep_for(std::chrono::nanoseconds(10));
            }
        }
        else
            return;
    }
}

void atomic_method(int* arr, bool is_sleep) {
    unsigned int counter = 0; 
    while (true)
    {
        counter = main_counter_atomic++;
        if (counter < NumTasks)
        {
            arr[counter]++;

            if (is_sleep)
            {
                std::this_thread::sleep_for(std::chrono::nanoseconds(sleep));
            }
        }
        else
            return;
    }
}

void task_1(int* a, int numbers)
{
    std::thread* threadArr = new std::thread[numbers];
    std::cout << std::endl << numbers << std::endl;
    std::cout << "Mutex method:" << std::endl;
    std::cout << "Without sleep" << std::endl;
    
    auto time_start_1 = clock();
    for (int i = 0; i< numbers; i++)
    {
        threadArr[i] = std::thread(mutex_method, a, false);
        threadArr[i].join();
    }
    auto time_1 = clock() - time_start_1;
    std::cout << "Time: " << time_1 << std::endl;
    main_counter_mutex = 0;
    main_counter_atomic = 0;
    std::cout << "With sleep" << std::endl;
    auto time_start_2 = clock();
    for (int i = 0; i < numbers; i++)
    {
        threadArr[i] = std::thread(mutex_method, a, true);
        threadArr[i].join();
    }
    auto time_2 = clock() - time_start_2;
    std::cout << "Time: " << time_2 << std::endl;
    main_counter_mutex = 0;
    main_counter_atomic = 0;
    std::cout << std::endl << "Atomic method." << std::endl;
  
    std::cout << "Without sleep" << std::endl;
    auto time_start_3 = clock();
    for (int i = 0; i < numbers; i++)
    {
        threadArr[i] = std::thread(atomic_method, a, false);
        threadArr[i].join();
    }
    auto time_3 = clock() - time_start_3;
    std::cout << "Time: " << time_3 << std::endl;
    main_counter_mutex = 0;
    main_counter_atomic = 0;
    std::cout << "With sleep" << std::endl;
    auto time_start_4 = clock();
    for (int i = 0; i < numbers; i++)
    {
        threadArr[i] = std::thread(atomic_method, a, true);
        threadArr[i].join();
    }
    auto time_4 = clock() - time_start_4;
    std::cout << "Time: " << time_4 << std::endl;
    main_counter_mutex = 0;
    main_counter_atomic = 0;
}


int main()
{
    int* arr = new int[NumTasks];
    for (int i = 0; i < NumTasks; i++)
    {
        arr[i] = 0;
    }
    
    for (int i = 0; i < 4; i++)
    {
        task_1(arr, NumThreads[i]);
    }

    return 0;
}
