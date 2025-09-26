#include "Engine.hpp"
#include <iostream>

namespace nlk
{
	Engine::Engine()
	{
		mRunning = true;
	}

	void Engine::Run()
	{
		std::cout << "NightLake Engine begins\n";
		while (mRunning)
		{

		}
	}
}


