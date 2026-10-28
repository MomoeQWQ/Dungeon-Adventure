#include "GamesEngineeringBase.h"
#include "./Core/DynamicArray.h"
#include "Game/Input.h"
#include "Core/Vec2.h"
#include "Render/Renderer.h"
#include "Render/TextureManager.h"
#include "Render/Camera.h"
#include "Entities/Player.h"
#include "Game/World.h"
#include "Game/Tilemap.h"
#include <iostream>

int main()
{
	bool running{ true };					//set game status running
	Input input{};							//input
	GamesEngineeringBase::Window canvas;	//window
	GamesEngineeringBase::Timer timer;		//timer
	Renderer renderer{ canvas };			//renderer
	Tilemap map{ 64,48,Vec2{32.0f,32.0f} }; //default map
	if (!map.loadFromFile("Resources/map1.txt"))
		return 1;                           //load map from file
	
	canvas.create(1024, 768, "Example");    //create window

	//Camera init(int worldWidth, int worldHeight,int screenWidth,int screenHeight)
	//We need to create camera after map cuz it relies on the latter one
	Camera camera(map.getPixelWidth(), map.getPixelHeight(), canvas.getWidth(), canvas.getHeight());
	
	//texture manager
	TextureManager tm;
	tm.load("player", "Resources/IDLE.png");
	const GamesEngineeringBase::Image* playerTexPtr = tm.get("player");
	if (playerTexPtr == nullptr)
	{
		std::cerr << "Failed to load Resources/IDLE.png" << std::endl;
		return 1;
	}

	//create World
	World world{};

	//create Player
	Vec2 playerPos{ 96,96 };
	Vec2 playerSize{ 112,96 };
	Player* playerPtr = new Player(playerPos, playerSize, playerTexPtr, &input, &map );
	world.add(playerPtr);
	
	// main loop of the game
	while (running) 
	{
		canvas.checkInput();

		input.update(canvas);

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
		renderer.clear();

		//draw map
		map.draw(renderer, camera);
		
		//test: drawbound
		//Rect bounds = playerPtr->getBounds();
		//Vec2 leftp = Vec2{ camera.worldToScreen(Vec2{ bounds.x,bounds.y }) };
		//renderer.drawRect(leftp.x, leftp.y, bounds.w, bounds.h, 255, 0, 0);

		//draw player
		world.draw(renderer, camera);  
		renderer.present();
	}
}