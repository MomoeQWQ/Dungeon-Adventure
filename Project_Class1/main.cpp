#include "GamesEngineeringBase.h"
#include "./Core/DynamicArray.h"
#include "Game/Input.h"
#include "Core/Vec2.h"
#include "Render/Renderer.h"
#include "Render/TextureManager.h"
#include "Render/Camera.h"
#include "Core/Config.h"
#include "Entities/Player.h"
#include "Game/World.h"
#include <iostream>

int main()
{
	bool running{ true };
	Input input{};                      //input
	GamesEngineeringBase::Window canvas;//window
	GamesEngineeringBase::Timer timer;  //timer
	Renderer renderer{ canvas };        //renderer
	
	canvas.create(1024, 768, "Example");

	//Camera init(int worldWidth, int worldHeight,int screenWidth,int screenHeight)
	Camera camera(WORLD_WIDTH, WORLD_HEIGHT, canvas.getWidth(), canvas.getHeight());
	
	//texture manager
	TextureManager tm;
	tm.load("player", "Resources/IDLE.png");
	const GamesEngineeringBase::Image* playerTexPtr = tm.get("player");

	//create World
	World world{};

	//create Player
	Vec2 playerPos{ 0,0 };
	Vec2 playerSize{ 112,96 };
	Player* playerPtr = new Player (playerPos,playerSize,playerTexPtr,&input);
	world.add(playerPtr);
	
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
		world.update(dt);

		//camera follow and calculate screenCoordinate
		camera.follow(playerPtr->getCenter());
		
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
		world.draw(renderer, camera);
		renderer.present();
	}
}