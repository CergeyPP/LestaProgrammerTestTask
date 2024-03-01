#include "Task1/Task1.h"
#include "Task2/Task2.h"

#include <iostream>
#include <cmath>

bool testTask1() {
	for (int i = 0; i < 10; i++)
	{
		int value = rand() % 201 - 100;
		std::cout << "Value: " << value << std::endl << "	Results:" << std::endl;
		
		bool sourceResult = isEven(value);
		bool taskResult = isEven2(value);

		std::cout << "	Source = " << sourceResult << "; Task = " << taskResult << std::endl;
		if (isEven(value) == isEven2(value))
		{
			std::cout << "	-> Test Succeed" << std::endl;
		}
		else
		{
			std::cout << "	-> Test Failed" << std::endl;
			return false;
		}
	}
	return true;
}

bool testTask2()
{
	RingBuffer<int> ringbuffer(5);
	for (int i = 0; i < 5; i++)
	{
		std::cout << "Try put " << i << ":\n";
		if (ringbuffer.tryPut(i))
		{
			std::cout << "	Put succeed -> Test Succeed" << std::endl;
		}
		else {
			std::cout << "	Put failed -> Test Failed" << std::endl;
			return false;
		}
	}

	for (int i = 6; i < 8; i++)
	{
		std::cout << "Try put " << i << " into full buffer:\n";
		if (!ringbuffer.tryPut(i))
		{
			std::cout << "	Put failed -> Test Succeed" << std::endl;
		}
		else {
			std::cout << "	Put succeed -> Test Failed" << std::endl;
			return false;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		std::cout << "Try get " << i << std::endl;
		int value;
		bool isGot = ringbuffer.tryGet(value);
		if (isGot && value == i)
		{
			std::cout << "	Get " << value << " Succeed, Expected " << i << " -> Test Succeed" << std::endl;
		}
		else {
			if (isGot)
				std::cout << "	Get " << value << " Succeed, Expected " << i << " -> Test Failed" << std::endl;
			else 
				std::cout << "	Get Failed -> Test Failed" << std::endl;
			return false;
		}
	}

	for (int i = 6; i < 8; i++)
	{
		std::cout << "Try get " << i << " from empty buffer" << std::endl;
		int value;
		bool isGot = ringbuffer.tryGet(value);
		if (!isGot)
		{
			std::cout << "	Get Failed -> Test Succeed" << std::endl;
		}
		else {
			std::cout << "	Get " << value << ", Expected fail -> Test Failed";
			return false;
		}
	}

	for (int i = 10; i < 12; i++)
	{
		std::cout << "Try put " << i << ":\n";
		if (ringbuffer.tryPut(i))
		{
			std::cout << "	Put succeed -> Test Succeed" << std::endl;
		}
		else {
			std::cout << "	Put failed -> Test Failed" << std::endl;
			return false;
		}
	}
	for (int i = 10; i < 12; i++)
	{
		std::cout << "Try get " << i << std::endl;
		int value;
		bool isGot = ringbuffer.tryGet(value);
		if (isGot && value == i)
		{
			std::cout << "	Get " << value << " Succeed, Expected " << i << " -> Test Succeed" << std::endl;
		}
		else {
			if (isGot)
				std::cout << "	Get " << value << " Succeed, Expected " << i << " -> Test Failed" << std::endl;
			else
				std::cout << "	Get Failed -> Test Failed" << std::endl;
			return false;
		}
	}

	return true;
}
bool testTask2CPP()
{
	RingBufferCPP<int> ringbuffer(5);
	for (int i = 0; i < 5; i++)
	{
		std::cout << "Try put " << i << ":\n";
		try
		{
			ringbuffer.put(i);
			std::cout << "	Put succeed -> Test Succeed" << std::endl;
		}
		catch (std::exception e)
		{
			std::cout << "	Put failed -> Test Failed" << std::endl;
			return false;
		}
	}

	for (int i = 6; i < 8; i++)
	{
		std::cout << "Try put " << i << " into full buffer:\n";
		try
		{
			ringbuffer.put(i);
			std::cout << "	Put succeed -> Test Failed" << std::endl;
			return false;
		}
		catch (std::exception e)
		{
			std::cout << "	Put failed -> Test Succeed" << std::endl;
		}
	}


	for (int i = 0; i < 5; i++)
	{
		std::cout << "Try get " << i << std::endl;
		auto value = ringbuffer.get();
		if (value)
		{
			if (value.value() == i)
				std::cout << "	Get " << value.value() << " Succeed, Expected " << i << " -> Test Succeed" << std::endl;
			else
			{
				std::cout << "	Get " << value.value() << " Succeed, Expected " << i << " -> Test Failed" << std::endl;
				return false;
			}
		}
		else {
			std::cout << "	Get Failed -> Test Failed" << std::endl;
			return false;
		}
	}

	for (int i = 6; i < 8; i++)
	{
		std::cout << "Try get " << i << "from empty buffer" << std::endl;
		auto value = ringbuffer.get();
		if (!value)
		{
			std::cout << "	Get Failed -> Test Succeed" << std::endl;
		}
		else {
			std::cout << "	Get " << value.value() << ", Expected fail -> Test Failed";
			return false;
		}
	}

	for (int i = 10; i < 12; i++)
	{
		std::cout << "Try put " << i << ":\n";
		try
		{
			ringbuffer.put(i);
			std::cout << "	Put succeed -> Test Succeed" << std::endl;
		}
		catch (std::exception e)
		{
			std::cout << "	Put failed -> Test Failed" << std::endl;
			return false;
		}
	}

	for (int i = 10; i < 12; i++)
	{
		std::cout << "Try get " << i << std::endl;
		auto value = ringbuffer.get();
		if (value)
		{
			if (value.value() == i)
				std::cout << "	Get " << value.value() << " Succeed, Expected " << i << " -> Test Succeed" << std::endl;
			else
			{
				std::cout << "	Get " << value.value() << " Succeed, Expected " << i << " -> Test Failed" << std::endl;
				return false;
			}
		}
		else {
			std::cout << "	Get Failed -> Test Failed" << std::endl;
			return false;
		}
	}

	return true;
}

int main() {
	std::cout << "Test of Task 1\n\n";
	if (!testTask1())
	{
		std::cout << "Test of Task 1 Failed, reject CV";
		return -1;
	}
	std::cout << "\nTesk of Task 2\n\n";
	if (!testTask2())
	{
		std::cout << "Test of Task 2 Failed, reject CV";
		return -1;
	}
	std::cout << "\nTesk of Task 2(CPP implementation)\n\n";
	if (!testTask2CPP())
	{
		std::cout << "Test of Task 2(CPP implementation) Failed, reject CV";
		return -1;
	}
	return 0;
}