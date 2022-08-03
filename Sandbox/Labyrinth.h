#pragma once
#include "Cell.h"
#include <cstdint>
#include <fstream>
#include <string>

class Labyrinth
{
public:
	Labyrinth();
	~Labyrinth();
	Cell* MoveToCell(int x, int y);

	int width;
	int height;
	int entry;
	int exit;

	Cell** cells;

	Cell* GetNeighbor(Cell c, uint8_t direction);

private:
	std::string datasetName;

	void CreateLabyrinth();
};