#include <iostream>
#include <fstream>
#include <vector>

#include "utils/Error.h"
#include "utils/utils.h"

Error err;

const int upperBorder = 300;
const int lowwerBorder = 1;

int N;
int M;
int stepCunter = 0;

void read(std::string fileName, std::vector<std::vector<int>>& array) {
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		err.addCriticalError("CANNOT READ FILE:" + fileName, "READ");
	}

	file >> N;
	file >> M;

	if (N < lowwerBorder && N > upperBorder)
	{
		err.addCriticalError("CANNOT READ FILE: OUT OF RANGE[1:300]", "READ");
	}
	//READ MAP
	array.resize(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (file.eof()) {
				err.addCriticalError("CANNOT READ FILE: UNEXPECTED EOF", "READ");
			}

			char temp;
			file >> temp;

			if (temp == '.') {
				array[i].push_back(0);
			}
			else {
				array[i].push_back(1);
			}

		}
	}
	//SET RAFT
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (array[i][j] != 0)
			{
				err.addCriticalError("CANNOT SET RAFT!", "READ");
			}
			array[i][j] = 2;
		}
	}

}

int main()
{
	clock_t start = clock();


	std::vector<std::vector<int>> map;
    read("INPUT.txt", map);
	print2dArrayVec(map);




	calculateTime(start);

    return 0;
}