#ifndef UTILS_H
#define UTILS_H

void calculateTime(clock_t  startTime, std::string functionName = "NULL");
template<typename T>
void print2dArrayVec(std::vector <std::vector<T>>& array) {
	for (int i = 0; i < array.size(); i++)
	{
		for (int j = 0; j < array[i].size(); j++)
		{
			std::cout << array[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

template<typename T>
void print2dArray(T& array) {
	for (int i = 0; i < array.size(); i++)
	{
		for (int j = 0; j < array[i].size(); j++)
		{
			std::cout << array[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

#endif // !UTILS_H