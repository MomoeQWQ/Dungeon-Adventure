#include "GamesEngineeringBase.h"
#include "./Core/DynamicArray.h"
#include "Game/Input.h"
#include "Core/Vec2.h"
#include <iostream>

int main()
{
	bool running{ true };
	Input input{};
	GamesEngineeringBase::Window canvas;
	GamesEngineeringBase::Timer timer;
	canvas.create(1024, 768, "Example");
	Vec2 position{0.0f,0.0f};
	constexpr float MOVE_SPEED = 300;
	constexpr int REC_SIZE = 30;

	// main loop of the game
	while (running) 
	{
		canvas.checkInput();

		input.update(canvas);

		canvas.clear();

		if (input.isDown(VK_ESCAPE))
		{
			running = false; // Exits the game loop
		}

		float dt = timer.dt();
		if (dt > 0.05f)
			dt = 0.05f;

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
		int width = canvas.getWidth();
		int height = canvas.getHeight();
		if (position.x < 0)
			position.x = 0;
		if (position.x > (width - REC_SIZE))
			position.x = (width - REC_SIZE);
		if (position.y < 0)
			position.y = 0;
		if (position.y > (height - REC_SIZE))
			position.y = (height - REC_SIZE);

		if (input.wasPressed('J'))
		{
			std::cout << "attack!";
		}

		for (int i = 0;i < REC_SIZE;i++) 
		{
			for (int j = 0;j < REC_SIZE;j++)
			{
				canvas.draw(static_cast<int>(position.x + i), static_cast<int>(position.y + j), 0, 0, 255);
			}
		}

		canvas.present();
	}
}