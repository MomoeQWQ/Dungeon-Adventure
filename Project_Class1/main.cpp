#include "GamesEngineeringBase.h"
#include "./Core/DynamicArray.h"
#include "Game/Input.h"
#include "Core/Vec2.h"
#include "Render/Renderer.h"
#include "Render/TextureManager.h"
#include "Render/Camera.h"
#include "Core/Config.h"
#include "Entities/Player.h"
#include <iostream>

int main()
{
	bool running{ true };
	Input input{};
	GamesEngineeringBase::Window canvas;
	Renderer renderer{ canvas };
	GamesEngineeringBase::Timer timer;

	canvas.create(1024, 768, "Example");
	//Camera init(int worldWidth, int worldHeight,int screenWidth,int screenHeight)
	Camera camera(WORLD_WIDTH, WORLD_HEIGHT, canvas.getWidth(), canvas.getHeight());
	
	//test for texture manager
	TextureManager tm;
	tm.load("player", "Resources/IDLE.png");
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




	//create Player
	Vec2 playerPos{ 0,0 };
	Vec2 playerSize{ 112,96 };
	Player player(playerPos,playerSize,ptr1,&input);

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
		
		//movement of player
		player.update(dt);

		//camera follow and calculate screenCoordinate
		camera.follow(player.getCenter());
		
		//clear canvas
		canvas.clear();

		//draw background(for test)
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

		//draw player
		player.draw(renderer, camera);
		renderer.present();
	}
}