#ifndef UTILS_H
#define UTILS_H

namespace Util {
	void calculateTime(clock_t  startTime, std::string functionName = "NULL");


	template<typename T>
	void pop_front(std::vector<T>& vec);

	template<typename T>
	void print2dArrayVec(std::vector <std::vector<T>>& array, int currPosX, int currPosY) {
		for (int i = 0; i < array.size(); i++)
		{
			for (int j = 0; j < array[i].size(); j++)
			{
				if (i == currPosY && j == currPosX)
				{
					std::cout << "X ";
					continue;
				}
				std::cout << array[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

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
	void print2dArray(T& array, int sizeX, int sizeY, int currPosX, int currPosY) {
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				if (i == currPosY && j == currPosX)
				{
					std::cout << "X ";
					continue;
				}
				std::cout << array[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	template<typename T>
	void print2dArray(T& array, int sizeX, int sizeY) {
		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				std::cout << array[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	
}

#endif // !UTILS_H