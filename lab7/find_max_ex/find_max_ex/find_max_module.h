#pragma once
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr[0];

	for (const auto element : arr)
	{
		if (less(maxValue, element))
		{
			maxValue = element;
		}
	}

	return true;
}