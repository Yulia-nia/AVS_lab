
// Netetskaya_lab_2_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <queue>
#include <atomic>

// ProducerNum = { 1, 2, 4 }
static const int ProducerNum = 1;
// ConsumerNum = { 1, 2, 4 }
static const int ConsumerNum = 1;
// TaskNum = 4 * 1024 * 1024
static const int TaskNum = 4 * 1024 * 1024;

std::atomic<int> result_sum     { 0 };
std::atomic<int> register_num   { 0 };
int some_sum = 0;

class Queue {
private:

    std::queue<uint8_t> _queue;
    std::mutex _mutex;

public:

    void push(uint8_t val) 
    {
        std::unique_lock<std::mutex> lck(_mutex);
        _queue.push(val);
    }

    bool pop(uint8_t& val) 
    {        
        std::unique_lock<std::mutex> lck(_mutex);
        // Если очередь пуста, ждем 1 мс записи в очередь.
        if (_queue.size() == 0) 
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        // Если очередь не пуста, помещает значение головы в val,
        // удаляет голову и возвращает true.
        if (_queue.size()!= 0) 
        {
            val = _queue.front();
            _queue.pop();
            return true;
        }
        // Если очередь по прежнему пуста, возвращаем false
        else
        {
            return false;
        }
    }
} que;

// Начинают читать очередь и прибавлять вычитанные значения к локальному счетчику.
void consumer_method() {
    uint8_t val = 0;

    while (true) 
    {
        if (que.pop(val))
        {
            some_sum += val;
            register_num++;
        }

        if (register_num >= TaskNum * ProducerNum)
        {
            break;
        }
    }
    result_sum.fetch_add(some_sum);
}

//Производитель записывает TaskNum единиц в очередь и завершает свою работу.
void producer_method() {
    int item = 0;
    while (item < TaskNum){
        que.push(1);
        item++;
    }
}

int main()
{
    std::vector<std::thread> prod;
    std::vector<std::thread> cons;

	for (int i = 0; i < ProducerNum; i++) {
        prod.push_back(std::thread(producer_method));
        prod[i].join();
	}

	for (int i = 0; i < ConsumerNum; i++) {
        cons.push_back(std::thread(consumer_method));
        cons[i].join();
	}

	std::cout << "Result sum:" << result_sum;
	return 0;
}
