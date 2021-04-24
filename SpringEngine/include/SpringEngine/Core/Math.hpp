#pragma once

#include <SpringEngine/core.hpp>

namespace SE
{
	int SE_API randomIntInRange(int min, int max);
	float SE_API randomFloatInRange(float min, float max);
	template <typename T>
	void bubbleSortVector(std::vector<T>& vector)
	{
		bool sorted = false;
		T tmpStorage;
		while (sorted == false)
		{
			sorted = true;
			for (unsigned int i = 0; i < vector.size()-1; i++)
			{
				if (vector[i + 1] < vector[i])
				{
					sorted = false;
					tmpStorage = vector[i];
					vector[i] = vector[i + 1];
					vector[i + 1] = tmpStorage;
				}
			}
		}
	}
}