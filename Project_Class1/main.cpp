#include "GamesEngineeringBase.h"
#include "Core/DynamicArray.h"
#include "Game/Input.h"
#include "Core/Vec2.h"
#include "Render/Renderer.h"
#include "Render/TextureManager.h"
#include "Render/Camera.h"
#include "Entities/Player.h"
#include "Game/World.h"
#include "Game/Tilemap.h"
#include "Render/BitmapFont.h"
#include "Core/FpsCounter.h"
#include "Entities/EnemyDef.h"
#include "Entities/Enemy.h"
#include "Entities/Spawner.h"
#include <iostream>
#include <string>

int main()
{
	bool running{ true };					//set game status running
	Input input{};							//input
	GamesEngineeringBase::Window canvas;	//window
	GamesEngineeringBase::Timer timer;		//timer
	Renderer renderer{ canvas };			//renderer
	FpsCounter fpscounter{};				//fpscounter

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
	tm.load("spawner", "Resources/HURT.png");
	const GamesEngineeringBase::Image* playerTexPtr = tm.get("player");
	const GamesEngineeringBase::Image* spawnerTexPtr = tm.get("spawner");
	if (playerTexPtr == nullptr)
	{
		std::cerr << "Failed to load Resources/IDLE.png" << std::endl;
		return 1;
	}
	if (spawnerTexPtr == nullptr)
	{
		std::cerr << "Failed to load Resources/HURT.png" << std::endl;
		return 1;
	}

	//load font
	BitmapFont font{};						
	font.load(tm.load("font","Resources/Font/SweetSunset+SweetSunrise/spritesheets/SweetSunset_bitmap_x2_rgba.png"));

	//create Player
	Vec2 playerPos{ 96,96 };
	Vec2 playerSize{ 112,96 };
	Player* playerPtr = new Player(playerPos, playerSize, playerTexPtr, 100, &map, &input );

	//create EnemyDefs
	EnemyDef def1 //balanced
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ playerTexPtr },
		.maxHp{ 30 },
		.contactDamage{ 10 },
		.speed{ 100 }
	};
	EnemyDef def2 //fast but squishy
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ playerTexPtr },
		.maxHp{ 15 },
		.contactDamage{ 5 },
		.speed{ 150 }
	};
	EnemyDef def3 //slow but tanky
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ playerTexPtr },
		.maxHp{ 80 },
		.contactDamage{ 20 },
		.speed{ 60 }
	};

	//create World
	World world{};

	world.add(playerPtr);
	world.add(new Spawner(Vec2{ 200.0f,200.0f }, playerSize, spawnerTexPtr, 100 , &map, &world, playerPtr, &def1, 5.0f));
	//world.add(new Enemy(Vec2{ 32.0f,32.0f }, &map, playerPtr, def1));
	//world.add(new Enemy(Vec2{ 32.0f,32.0f }, &map, playerPtr, def2));
	//world.add(new Enemy(Vec2{ 32.0f,32.0f }, &map, playerPtr, def3));

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
		//before restrict dt,use raw dt to update fps
		fpscounter.update(dt);

		if (dt > 0.05f)
			dt = 0.05f;

		if (input.wasPressed('J'))
		{
			std::cout << "attack!";
			playerPtr->takeDamage(10);
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

		//draw fps
		font.drawText(renderer, "FPS: " + std::to_string(fpscounter.getFps()), camera.getScreenWidth()-font.measureText("FPS: 999")-10, 10);

		//draw Hp bar
		font.drawText(renderer, "^", 10, 10);
		renderer.drawRect(font.measureText("^") + 20, (41 - 10) / 2, 200, 30, 105, 105, 105);
		renderer.drawRect(font.measureText("^") + 20, (41 - 10) / 2, 200 * static_cast<float>(playerPtr->getHp()) / playerPtr->getMaxHp(), 30, 244, 128, 128);
		font.drawText(renderer, std::to_string(playerPtr->getHp()) + "/" + std::to_string(playerPtr->getMaxHp()), font.measureText("^") + 230, 9);

		renderer.present();
	}
}