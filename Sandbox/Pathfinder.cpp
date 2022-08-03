#include "Pathfinder.h"
#include <iostream>
#include <Windows.h>

Pathfinder::Pathfinder(Labyrinth* l)
{
	labyrinth = l;
	currentCell = &labyrinth->cells[labyrinth->entry - 1][0];
	labyrinth->cells[currentCell->x][currentCell->y].visited = true;
	
	hasFoundExit = false;

	// PrintLabyrinth();
}

Pathfinder::~Pathfinder()
{
	delete labyrinth;
}

void Pathfinder::getMoves()
{
	canMoveNorth = allMoves & NORTH;
	canMoveSouth = allMoves & SOUTH;
	canMoveEast = allMoves & EAST;
	canMoveWest = allMoves & WEST;
}

void Pathfinder::PrintLabyrinth()
{
	system("CLS");

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < labyrinth->height; i++)
	{
		std::cout << '\n';

		for (int j = 0; j < labyrinth->width; j++)
		{
			if (currentCell->x == j && currentCell->y == i)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
				std::cout << 1;
			}
			else if (labyrinth->cells[j][i].visited)
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
				std::cout << 1;
			}
			else
			{
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
				std::cout << "0";
			}
		}
	}
}

void Pathfinder::DrawLabyrinth()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hConsole, { (short)(currentCell->x + 1), (short)(currentCell->y + 1)});
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	std::cout << 1;

	Sleep(0);
}

void Pathfinder::MakeMove()
{
	// DrawLabyrinth();

	if (currentCell->y == labyrinth->height - 1 && currentCell->x == labyrinth->exit - 1)
	{
		hasFoundExit = true;
		return;
	}

	allMoves = ~currentCell->value;
	allMoves ^= 240;

	if ((allMoves & (allMoves - 1)) != 0 && !currentCell->hasVisitedAllNeighbors && !currentCell->isKnownIntersection)
	{
		labyrinth->cells[currentCell->x][currentCell->y].isKnownIntersection = true;
		intersections.push_back({ currentCell->x, currentCell->y });
	}

	getMoves();

	if (canMoveEast && labyrinth->GetNeighbor(*currentCell, EAST)->visited == false && !hasFoundExit)
	{
		currentCell = labyrinth->GetNeighbor(*currentCell, EAST);
		labyrinth->cells[currentCell->x][currentCell->y].visited = true;
		return;
	}

	if (canMoveWest && labyrinth->GetNeighbor(*currentCell, WEST)->visited == false && !hasFoundExit)
	{
		currentCell = labyrinth->GetNeighbor(*currentCell, WEST);
		labyrinth->cells[currentCell->x][currentCell->y].visited = true;
		return;
	}

	if (canMoveNorth && labyrinth->GetNeighbor(*currentCell, NORTH)->visited == false && !hasFoundExit)
	{
		if (!(currentCell->y == 0))
		{
			currentCell = labyrinth->GetNeighbor(*currentCell, NORTH);
			labyrinth->cells[currentCell->x][currentCell->y].visited = true;
			return;
		}
	}

	if (canMoveSouth && labyrinth->GetNeighbor(*currentCell, SOUTH)->visited == false && !hasFoundExit)
	{
		currentCell = labyrinth->GetNeighbor(*currentCell, SOUTH);
		labyrinth->cells[currentCell->x][currentCell->y].visited = true;
		return;
	}

	else
	{
		if (hasFoundExit)
			return;

		labyrinth->cells[currentCell->x][currentCell->y].hasVisitedAllNeighbors = true;
		labyrinth->cells[intersections.back().x][intersections.back().y].isKnownIntersection = false;
		currentCell = labyrinth->MoveToCell(intersections.back().x, intersections.back().y);

		intersections.pop_back();

		return;
	}
}