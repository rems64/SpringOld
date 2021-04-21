#include <SpringEngine/Core/Math.hpp>
namespace SE
{
	int randomIntInRange(int min, int max)
	{
		return (int)((float)rand() / RAND_MAX) * (max - min) + min;
	}

	float randomFloatInRange(float min, float max)
	{
		return ((float)rand() / RAND_MAX) * (float)(max - min) + min;
	}
}
