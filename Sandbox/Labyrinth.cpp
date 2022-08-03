#include "Labyrinth.h"

Labyrinth::Labyrinth()
{
	Labyrinth::CreateLabyrinth();
}

Labyrinth::~Labyrinth()
{
	delete cells;
}

Cell* Labyrinth::MoveToCell(int x, int y)
{
	return &cells[x][y];
}

Cell* Labyrinth::GetNeighbor(Cell c, uint8_t direction)
{
	switch (direction)
	{
	case 1:
		return &cells[c.x][c.y - 1];
	case 2:
		return &cells[c.x][c.y + 1];
	case 4:
		return &cells[c.x + 1][c.y];
	case 8:
		return &cells[c.x - 1][c.y];
	default:
		break;
	}
}

void Labyrinth::CreateLabyrinth()
{
	std::string lineToSeparate;

	std::fstream myReadFile("c:\\data\\labyrinth\\1000x1000_25534.dat");

	std::getline(myReadFile, datasetName);

	std::getline(myReadFile, lineToSeparate);
	sscanf_s(lineToSeparate.c_str(), "%i %i", &width, &height);

	std::getline(myReadFile, lineToSeparate);
	sscanf_s(lineToSeparate.c_str(), "%i %i", &entry, &exit);

	cells = new Cell * [width] {};
	for (int i = 0; i < width; i++)
	{
		cells[i] = new Cell[height];
	}

	std::string s_cellBits;

	for (int i = 0; i < height; i++)
	{
		int kOffset = 0;
		std::getline(myReadFile, lineToSeparate);

		for (int j = 0; j < width; j++)
		{
			s_cellBits = "";

			for (int k = kOffset; k < lineToSeparate.size(); k++)
			{

				s_cellBits += lineToSeparate[k];
				kOffset++;

				if (lineToSeparate[k] == ',' || k == lineToSeparate.size() - 1)
				{
					cells[j][i].value = atoi(s_cellBits.c_str());
					cells[j][i].x = j;
					cells[j][i].y = i;
					break;
				}
			}
		}
	}
}