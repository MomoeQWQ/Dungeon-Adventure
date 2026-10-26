#include "GamesEngineeringBase.h"
#include "./Core/DynamicArray.h"
#include "Game/Input.h"
#include "Core/Vec2.h"
#include "Render/Renderer.h"
#include <iostream>

int main()
{
	bool running{ true };
	Input input{};
	GamesEngineeringBase::Window canvas;
	Renderer renderer{ canvas };
	GamesEngineeringBase::Timer timer;
	Vec2 position{0.0f,0.0f};
	GamesEngineeringBase::Image image;

	canvas.create(1024, 768, "Example");
	image.load("Resources/A.png");
	constexpr float MOVE_SPEED = 300;

	// main loop of the game
	while (running) 
	{
		canvas.checkInput();

		input.update(canvas);

		renderer.clear();

		if (input.isDown(VK_ESCAPE))
		{
			running = false; // Exits the game loop
		}

		float dt = timer.dt();
		if (dt > 0.05f)
			dt = 0.05f;

		if (input.wasPressed('J'))
		{
			std::cout << "attack!";
		}

		Vec2 unit{ 0.0f,0.0f };
		if (input.isDown('W'))
			unit += Vec2{ 0.0f,-1.0f };
		if (input.isDown('A'))
			unit += Vec2{ -1.0f,0.0f };
		if (input.isDown('S'))
			unit += Vec2{ 0.0f,1.0f };
		if (input.isDown('D'))
			unit += Vec2{ 1.0f,0.0f };
		unit.normalize();

		position += unit * dt * MOVE_SPEED;
		
		renderer.drawImage(image,static_cast<int>(position.x), static_cast<int>(position.y));

		renderer.present();
	}
}