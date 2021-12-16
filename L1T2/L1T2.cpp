#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <assert.h>
#include <map>
#include <set>

#include "utils/Error.h"
#include "utils/utils.h"

/*
EXAMPLES FOR INPUT

5
.....
.@@..
.....
.....
.....

5
@..@.
..##.
.....
.....
.....

5
@....
..#..
.#...
.....
....@


*/


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
	int mark = 0;
};

enum Directions
{
	/*

	U - UP
	R - RIGHT
	D - DOWN
	L - LEFT

	UL - UP LEFT AND E.T.C

	*/

	UL,
	UR,
	RU,
	RD,
	DR,
	DL,
	LD,
	LU
}; 
static const Directions All[] = { UL,
	UR,
	RU,
	RD,
	DR,
	DL,
	LD,
	LU };

Pos startPos;
Pos endPos;


std::vector<std::vector<int>> map;
std::vector<std::vector<int>> mapOfSteps;
std::map<std::vector<int>, Directions> origins;
std::vector<Me> queue;
bool res = false;

int N;
const int lowwerBorder = 2;
const int upperBorder = 300;

//DOESN'T WORK FROM HEADER
//TODO: MAKE IT WORK FROM UTILS
template<typename T>
void pop_front(std::vector<T>& vec)
{
	assert(!vec.empty());
	vec.erase(vec.begin());
}


void read(std::string fileName) 
{
	std::ifstream file;
	file.open(fileName);
	if (!file.is_open()) 
	{
		err.addCriticalError("CANNOT READ FILE:" + fileName, "READ");
	}
	int n = 0;
	file >> N;

	if (N < lowwerBorder && N > upperBorder)
	{
		err.addCriticalError("CANNOT READ FILE: OUT OF RANGE[2:300]", "READ");
	}
	//READ MAP
	map.resize(N + 2);
	mapOfSteps.resize(N + 2);
	for (int i = 0; i <= N + 1; i++)
	{
		for (int j = 0; j <= N + 1; j++)
		{
			map[i].push_back(1);
			mapOfSteps[i].push_back(0);
		}
	}
	for (int i = 1; i < N + 1; i++)
	{
		for (int j = 1; j < N + 1; j++)
		{
			if (file.eof()) 
			{
				err.addCriticalError("CANNOT READ FILE: UNEXPECTED EOF", "READ");
			}

			char temp;
			file >> temp;

			if (temp == '.') 
			{
				map[i][j] = 0;
			}
			else if (temp == '#') 
			{
				map[i][j] = 1;
			}
			else
			{
				map[i][j] = 0;
				if (n == 0)
				{
					startPos = { j, i };
					n++;
					continue;
				}
				if (n == 1)
				{
					endPos = { j, i };
					n++;
					continue;
				}
				if (n > 2)
				{
					err.addCriticalError("GIVEN MORE THAN TWO POINTS", "READ");
				}
			}
		}
	}
}

void addToQueue(int& u, int& v, int& mark) 
{
	if (endPos.x == u && endPos.y == v)
	{
		res = true;
		mapOfSteps[v][u] = mark;
		return;
	}
	queue.push_back({ u, v, mark + 1 });
}

void printConditions() 
{
	std::cout << "StartPos: " << startPos.x << ":" << startPos.y << std::endl <<
		"EndPos: " << endPos.x << ":" << endPos.y << std::endl;
}

void printAll(int delay = 0, bool clear = false) {
	printConditions();
	Util::print2dArrayVec(map);
	std::cout << std::endl;
	Util::print2dArrayVec(mapOfSteps);
	Sleep(delay);
	if (clear)
	{
		system("CLS");
	}
}

void printAll(int posX, int posY, int delay = 0, bool clear = false) 
{
	printConditions();
	Util::print2dArrayVec(map, posX, posY);
	std::cout << std::endl;
	Util::print2dArrayVec(mapOfSteps);
	Sleep(delay);
	if (clear)
	{
		system("CLS");
	}
}


void move(Directions dir,int posX, int posY, int mark)
{
	int dx = 0;
	int dy = 0;
	switch (dir)
	{
	case UL:
		dx = -1;
		dy = -2;
		break;
	case UR:
		dx = 1;
		dy = -2;
		break;
	case RU:
		dx = 2;
		dy = -1;
		break;
	case RD:
		dx = 2;
		dy = 1;
		break;
	case DR:
		dx = 1;
		dy = 2;
		break;
	case DL:
		dx = -1;
		dy = 2;
		break;
	case LD:
		dx = -2;
		dy = 1;
		break;
	case LU:
		dx = -2;
		dy = -1;
		break;
	default:
		dx = 0;
		dy = 0;
		break;
	}

	Pos temp = { posX + dx, posY + dy };

	if ((temp.x > 0) && (temp.y > 0) && (temp.x < (N + 2)) && (temp.y < (N + 2)) && (map[temp.y][temp.x] == 0) && (mapOfSteps[temp.y][temp.x] == 0))
	{
		mapOfSteps[temp.y][temp.x] = mark;
		addToQueue(temp.x, temp.y, mark);
		std::vector<int> vec = { temp.x, temp.y };
		origins.insert(std::make_pair(vec, dir));
		std::cout << "Moved from: " << posX << ":" << posY << " to " << temp.x << ":" << temp.y << std::endl;
		//printAll(temp.x, temp.y, 0, true); //UNCOMMENT FOR DEBUG
	}
}

int main()
{
	clock_t start = clock();

    read("INPUT.txt");
	
	//printAll(startPos.x, startPos.y, 0, true); //UNCOMMENT FOR DEBUG

	int mark = 1;
	addToQueue(startPos.x, startPos.y, mark);
	mapOfSteps[startPos.y][startPos.x] = 1;
	while (!queue.empty())
	{
		Me obj = queue.front();
		pop_front(queue);
		
		for (int i = 0; i < Directions::LU; i++)
		{
			move(All[i], obj.x, obj.y, obj.mark);
			if (res == true) break;
		}
	}

	//printAll(); //UNCOMMENT FOR DEBUG

	std::cout << res << std::endl;

	std::ofstream ofile("OUTPUT.txt");

	if (res)
	{
		char** array{ new char* [N] };
		for (int i = 0; i < N; i++)
		{
			array[i] = new char[N];
			for (int j = 0; j < N; j++)
			{
				array[i][j] = '.';
			}
		}

		for (int i = 1; i < N + 1; i++)
		{
			for (int j = 1; j < N + 1; j++)
			{
				if (map[i][j] == 1)
				{
					array[i - 1][j - 1] = '#';
				}
			}
		}

		auto coord = origins.find({ endPos.x, endPos.y });
		array[endPos.y - 1][endPos.x - 1] = '@';
		while (true) {
			std::cout << coord->first[0] << ":" << coord->first[1] << std::endl;
			Directions origin = origins[{coord->first[0], coord->first[1]}];
			int dx = 0;
			int dy = 0;
			switch (origin)
			{
			case UL:
				dx = 1;
				dy = 2;
				break;
			case UR:
				dx = -1;
				dy = 2;
				break;
			case RU:
				dx = -2;
				dy = 1;
				break;
			case RD:
				dx = -2;
				dy = -1;
				break;
			case DR:
				dx = -1;
				dy = -2;
				break;
			case DL:
				dx = 1;
				dy = -2;
				break;
			case LD:
				dx = 2;
				dy = -1;
				break;
			case LU:
				dx = 2;
				dy = 1;
				break;
			default:
				dx = 0;
				dy = 0;
				break;
			}

			Pos temp = { coord->first[0] + dx, coord->first[1] + dy };
			array[temp.y - 1][temp.x - 1] = '@';
			//Util::print2dArray(array, N, N); //UNCOMMENT FOR DEBUG
			if (temp.x == startPos.x && temp.y == startPos.y)
				break;
			else
				coord = origins.find({ temp.x, temp.y });
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N ; j++)
			{
				ofile << array[i][j];
			}
			ofile << std::endl;
		}
		
	}
	else {
		ofile << "Impossible" << std::endl;
	}

	Util::calculateTime(start);

    return 0;
}