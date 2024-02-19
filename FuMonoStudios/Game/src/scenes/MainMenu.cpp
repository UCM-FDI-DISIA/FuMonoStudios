#include "MainMenu.h"

ecs::MainMenu::MainMenu()
{
	init();
}

ecs::MainMenu::~MainMenu()
{
}

void ecs::MainMenu::init()
{
	std::cout << "Hola Menu" << std::endl;
	sdlutils().clearRenderer();
}
