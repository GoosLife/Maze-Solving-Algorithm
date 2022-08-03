#pragma once
class Cell
{
public:
	Cell() { visited = false; hasVisitedAllNeighbors = false; isKnownIntersection = false; }
	int value;
	int x;
	int y;
	bool visited;
	bool hasVisitedAllNeighbors;
	bool isKnownIntersection;
};

