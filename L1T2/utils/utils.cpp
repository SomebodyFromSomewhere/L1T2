#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <assert.h>
#include "utils.h"

namespace Util {

	void calculateTime(clock_t  startTime, std::string functionName)
	{
		clock_t endTime = clock();
		double seconds = (double)(endTime - double(startTime)) / CLOCKS_PER_SEC;
		if (functionName == "NULL")
		{
			std::cout << "EXECUTION TIME : " << seconds << std::endl;
		}
		else
		{
			std::cout << "[" << functionName << "]EXECUTION TIME : " << seconds << std::endl;
		}
	}

	template<typename T>
	void pop_front(std::vector<T>& vec)
	{
		assert(!vec.empty());
		vec.erase(vec.begin());
	}
}