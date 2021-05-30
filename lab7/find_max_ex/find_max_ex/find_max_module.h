#pragma once

#include <algorithm>
#include <vector>

template <typename T, typename Less>
bool FindMaxEx(const std::vector<T>& arr, T& maxValue, const Less& less)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = *std::max_element(arr.begin(), arr.end(), less);

	return true;
}