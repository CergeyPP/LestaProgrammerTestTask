#pragma once
#include <stdint.h>
#include <memory>

template<typename T>
void mergeSort(T* source_array, size_t size)
{
	if (size <= 1)
		return;

	size_t left_size = size / 2;
	size_t right_size = size - left_size;

	mergeSort(&source_array[0], left_size);
	mergeSort(&source_array[size / 2], right_size);

	size_t left_it = 0;
	size_t right_it = left_size;
	size_t index = 0;

	std::unique_ptr<T[]> buffer(new T[size]);

	while (left_it < left_size || right_it < size)
	{
		if (source_array[left_it] < source_array[right_it])
		{
			buffer[index++] = std::move(source_array[left_it++]);
			if (left_it == left_size)
			{
				std::copy(std::make_move_iterator(&source_array[right_it]),
					std::make_move_iterator(&source_array[size]),
					&buffer[index]);
				break;
			}
		}
		else
		{
			buffer[index++] = std::move(source_array[right_it++]);
			if (right_it == size)
			{
				std::copy(std::make_move_iterator(&source_array[left_it]),
					std::make_move_iterator(&source_array[left_size]),
					&buffer[index]);
				break;
			}
		}
	}

	std::copy(std::make_move_iterator(buffer.get()),
		std::make_move_iterator(&buffer[size]),
		source_array);
}