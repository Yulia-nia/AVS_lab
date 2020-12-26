#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>
#include <random>


int vector_size = 1000000;

// Вариант 17. Скалярное произведение двух векторов.

void parallel(const std::vector<int>& vector_1, const std::vector<int>& vector_2)
{
	auto start_time = clock();
	int result = 0;	
#pragma omp parallel for shared(vector_1,vector_2,result) private(i) schedule(auto) reduction(+:result)
	for (int i = 0; i < vector_size; i++)
	{
		result += vector_1[i] * vector_2[i];
	}
	auto time = clock() - start_time;
	std::cout << "Parallel computation." << std::endl<< "Result:" << result << std::endl<< "Time: " << time << std::endl;
}

void simple(const std::vector<int>& vector_1, const std::vector<int>& vector_2)
{
	auto start_time = clock();

	int result = 0;

	for (int i = 0; i < vector_size; i++)
	{
		result += vector_1[i] * vector_2[i];
	}
	auto time = clock() - start_time;
	std::cout << "One branch."<< result << std::endl<< "Result:" << result << std::endl<< "Time: " << time << std::endl;
}



int main()
{
	std::vector<int> vector_1(vector_size, 1), vector_2(vector_size, 1);

	for (int i = 0; i < vector_size; i++)
	{
		vector_1[i] = rand() % 10;
	}

	for (int i = 0; i < vector_size; i++)
	{
		vector_2[i] = rand() % 10;
	}

	simple(vector_1, vector_2);
	parallel(vector_1, vector_2);

	return 0;
}