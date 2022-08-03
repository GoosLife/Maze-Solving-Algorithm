#pragma once
#include "Cell.h"
#include "Labyrinth.h"
#include <cstdint>
#include <vector>

struct Coordinates
{
public:
	int x;
	int y;
};

class Pathfinder
{
public:
	Pathfinder(Labyrinth* l);
	~Pathfinder();
	
	void MakeMove();

	bool canMoveNorth;
	bool canMoveSouth;
	bool canMoveEast;
	bool canMoveWest;

	uint8_t allMoves;
	std::vector<Coordinates> intersections;

	Labyrinth* labyrinth;
	Cell* currentCell;

	bool hasFoundExit;

private:
	const int NORTH = 1;
	const int SOUTH = 2;
	const int EAST = 4;
	const int WEST = 8;


	void getMoves();
	void PrintLabyrinth();
	void DrawLabyrinth();
};

