#pragma once

#include "NightLake.hpp"

class Game : public nle::Application
{
public:
	Game();
	Game(nle::AppSpecifications& appSpecs);
	~Game();
};