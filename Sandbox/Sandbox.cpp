#include "Cell.h"
#include "Labyrinth.h"
#include "Pathfinder.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>


int main()
{
	for (int i = 0; i < 100; i++)
	{
		Labyrinth* l = new Labyrinth();
	
		Pathfinder p(l);

		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		while (!p.hasFoundExit)
		{
			// std::cout << "Iteration " << i << '\n';
			p.MakeMove();
			// Sleep(1000);
			// i++;
		}

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "Time elapsed = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms" << std::endl;
	}
}