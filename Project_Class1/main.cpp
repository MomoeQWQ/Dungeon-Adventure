// main loop of the game
#include "GamesEngineeringBase.h"
#include "./Core/DynamicArray.h"
#include "Game/Input.h"
#include <iostream>

int main()
{
	bool running{ true };
	Input input{};
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "Example");

	while (running) 
	{
		if (canvas.keyPressed(VK_ESCAPE))
		{
			break; // Exits the game loop
		}

		canvas.checkInput();
		input.update(canvas);
		if (input.wasPressed('J'))
		{
			std::cout << "attack!";
		}

		canvas.present();
	}
}