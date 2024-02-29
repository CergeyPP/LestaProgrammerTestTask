#include "Task1/Task1.h"

#include <iostream>
#include <cmath>

bool testTask1() {
	std::cout << "Test Task ¹1" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		int value = rand() % 201 - 100;
		std::cout << "Value: " << value << " -> ";
		if (isEven(value) == isEven2(value))
		{
			std::cout << "Verified" << std::endl;
		}
		else
		{
			std::cout << "Failed" << std::endl;
			return false;
		}
	}
	return true;
}

int main() {
	testTask1();
	return 0;
}