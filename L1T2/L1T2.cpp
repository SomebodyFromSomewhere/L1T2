#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>

#include "utils/Error.h"
#include "utils/utils.h"

Error err;
struct Pos
{
	int x;
	int y;
};
struct Me 
{
	int x;
	int y;
	int mark;
};

Pos start;
Pos end;

std::vector<Pos> queue;

int N;
const int lowwerBorder = 2;
const int upperBorder = 300;
 
void read(std::string fileName, std::vector<std::vector<int>>& array) {
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		err.addCriticalError("CANNOT READ FILE:" + fileName, "READ");
	}
	int n = 0;
	file >> N;

	if (N < lowwerBorder && N > upperBorder)
	{
		err.addCriticalError("CANNOT READ FILE: OUT OF RANGE[2:300]", "READ");
	}
	//READ MAP
	array.resize(N + 2);
	for (int i = 0; i <= N + 1; i++)
	{
		for (int j = 0; j <= N + 1; j++)
		{
			array[i].push_back(1);
		}
		//std::cout << i << std::endl;
	}
	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 1; j < N + 1; j++)
		{
			if (file.eof()) {
				err.addCriticalError("CANNOT READ FILE: UNEXPECTED EOF", "READ");
			}

			char temp;
			file >> temp;

			if (temp == '.') {
				array[i][j] = 0;
			}
			else if (temp == '#') {
				array[i][j] = 1;
			}
			else
			{
				array[i][j] = 0;
				if (n == 0)
				{
					start = { i, j };
					n++;
				}
				if (n == 1)
				{
					end = { i, j };
					n++;
				}
				if (n > 2)
				{
					err.addCriticalError("GIVEN MORE THAN TWO POINTS", "READ");
				}
			}
		}
	}
}

void addToQueue(int& u, int& v, bool& res) {
	if (end.x == u && end.y == v)
	{
		res = true;
	}
	queue.push_back({ u, v });

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