#include "GamesEngineeringBase.h"
#include "./Core/DynamicArray.h"
#include "Game/Input.h"
#include "Core/Vec2.h"
#include "Render/Renderer.h"
#include "Render/TextureManager.h"
#include "Render/Camera.h"
#include <iostream>

int main()
{
	constexpr int WORLD_WIDTH = 2048;
	constexpr int WORLD_HEIGHT = 1536;
	constexpr float MOVE_SPEED = 300;

	bool running{ true };
	Input input{};
	GamesEngineeringBase::Window canvas;
	Renderer renderer{ canvas };
	GamesEngineeringBase::Timer timer;
	Vec2 position{0.0f,0.0f};

	canvas.create(1024, 768, "Example");
	//Camera init(int worldWidth, int worldHeight,int screenWidth,int screenHeight)
	Camera camera(WORLD_WIDTH, WORLD_HEIGHT, canvas.getWidth(), canvas.getHeight());
	
	//test for texture manager
	TextureManager tm;
	tm.load("player", "Resources/A.png");
	const GamesEngineeringBase::Image* ptr1 = tm.get("player");
	//const GamesEngineeringBase::Image* ptr1_5 = tm.load("player", "Resources/A.png");//test if loaded only once
	//const GamesEngineeringBase::Image* ptr2 = tm.get("player");
	//if (ptr1 == ptr2)
	//	std::cout << "same ptr!"<< std::endl;
	//if (ptr1 == ptr1_5)
	//	std::cout << "same ptr!" << std::endl;

	//const GamesEngineeringBase::Image* ptr3 = tm.get("enemy");
	//std::cout << ptr3 << std::endl;

	//tm.load("bad", "Resources/nope.png");
	//const GamesEngineeringBase::Image* ptr4 = tm.get("bad");
	//std::cout << ptr4 << std::endl;

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

		position += unit * dt * MOVE_SPEED;//calculate the position

		//limit the position in the world range
		float endX = static_cast<float>(WORLD_WIDTH) - static_cast<int>(ptr1->width);
		float endY = static_cast<float>(WORLD_HEIGHT) - static_cast<int>(ptr1->height);
		if (position.x < 0)
			position.x = 0;
		if (position.x > endX)
			position.x = endX;
		if (position.y < 0)
			position.y = 0;
		if (position.y > endY)
			position.y = endY;
		
		//camera follow and calculate screenCoordinate
		Vec2 cpoint{ position.x + ptr1->width / 2,position.y + ptr1->height / 2 };
		camera.follow(cpoint);
		Vec2 screenCoord{ camera.worldToScreen(position) };
		
		//paint background(for test)
		for (int row = 0; row < WORLD_HEIGHT / 64; row++)
		{
			for (int col = 0;col < WORLD_WIDTH / 64;col++)
			{
				Vec2 blockcoord{ static_cast<float>(col * 64),static_cast<float>(row * 64) };
				Vec2 screenblockcoord = camera.worldToScreen(blockcoord);
				if ((row + col) % 2)
					renderer.drawRect(static_cast<int>(screenblockcoord.x), static_cast<int>(screenblockcoord.y), 64, 64,0,0,0);
				else
					renderer.drawRect(static_cast<int>(screenblockcoord.x), static_cast<int>(screenblockcoord.y), 64, 64, 255, 255, 255);
			}
		}

		//now use pointer from TextureManager to load image
		renderer.drawImage(*ptr1,static_cast<int>(screenCoord.x), static_cast<int>(screenCoord.y));
		renderer.present();
	}
}