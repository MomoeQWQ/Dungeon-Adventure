#include "GamesEngineeringBase.h"
#include "Core/DynamicArray.h"
#include "Core/Vec2.h"
#include "Core/FpsCounter.h"
#include "Render/Renderer.h"
#include "Render/TextureManager.h"
#include "Render/Camera.h"
#include "Render/BitmapFont.h"
#include "Game/Input.h"
#include "Game/World.h"
#include "Game/Tilemap.h"
#include "Game/GameState.h"
#include "Entities/Player.h"
#include "Entities/EnemyDef.h"
#include "Entities/Enemy.h"
#include "Entities/Spawner.h"
#include "Entities/ProjectileDef.h"
#include "Entities/HeroDef.h"
#include <iostream>
#include <string>


int main()
{
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
	tm.load("bullet", "Resources/bullet.png");
	tm.load("magicbullet", "Resources/magic.png");
	tm.load("enemy_balanced", "Resources/enemy_balanced.png");
	tm.load("enemy_fast", "Resources/enemy_fast.png");
	tm.load("enemy_tank", "Resources/enemy_tank.png");
	tm.load("spawner_new", "Resources/spawner.png");
	tm.load("hero_warrior", "Resources/hero_warrior.png");
	tm.load("hero_ranger", "Resources/hero_ranger.png");
	tm.load("hero_mage", "Resources/hero_mage.png");
	tm.load("tile_floor", "Resources/tile_floor.png");
	tm.load("tile_wall", "Resources/tile_wall.png");
	tm.load("enemy_bullet", "Resources/enemy_bullet.png");
	tm.load("potion_hp", "Resources/potion_hp.png");
	tm.load("potion_mp", "Resources/potion_mp.png");
	tm.load("key", "Resources/key.png");
	tm.load("door_closed", "Resources/door_closed.png");
	tm.load("door_open", "Resources/door_open.png");
	tm.load("trap_spikes", "Resources/trap_spikes.png");
	tm.load("trap_turret", "Resources/trap_turret.png");
	tm.load("switch_off", "Resources/switch_off.png");
	tm.load("switch_on", "Resources/switch_on.png");
	tm.load("help_button", "Resources/help_button.png");

	const GamesEngineeringBase::Image* playerTexPtr = tm.get("player");
	const GamesEngineeringBase::Image* bulletTexPtr = tm.get("bullet");
	const GamesEngineeringBase::Image* magicTexPtr = tm.get("magicbullet");
	const GamesEngineeringBase::Image* enemyBalancedTexPtr = tm.get("enemy_balanced");
	const GamesEngineeringBase::Image* enemyFastTexPtr = tm.get("enemy_fast");
	const GamesEngineeringBase::Image* enemyTankTexPtr = tm.get("enemy_tank");
	const GamesEngineeringBase::Image* spawnerNewTexPtr = tm.get("spawner_new");
	const GamesEngineeringBase::Image* warriorTexPtr = tm.get("hero_warrior");
	const GamesEngineeringBase::Image* rangerTexPtr = tm.get("hero_ranger");
	const GamesEngineeringBase::Image* mageTexPtr = tm.get("hero_mage");
	const GamesEngineeringBase::Image* floorTexPtr = tm.get("tile_floor");
	const GamesEngineeringBase::Image* wallTexPtr = tm.get("tile_wall");
	const GamesEngineeringBase::Image* enemyBulletTexPtr = tm.get("enemy_bullet");
	const GamesEngineeringBase::Image* potionHpTexPtr = tm.get("potion_hp");
	const GamesEngineeringBase::Image* potionMpTexPtr = tm.get("potion_mp");
	const GamesEngineeringBase::Image* keyTexPtr = tm.get("key");
	const GamesEngineeringBase::Image* doorClosedTexPtr = tm.get("door_closed");
	const GamesEngineeringBase::Image* doorOpenTexPtr = tm.get("door_open");
	const GamesEngineeringBase::Image* trapSpikesTexPtr = tm.get("trap_spikes");
	const GamesEngineeringBase::Image* trapTurretTexPtr = tm.get("trap_turret");
	const GamesEngineeringBase::Image* switchOffTexPtr = tm.get("switch_off");
	const GamesEngineeringBase::Image* switchOnTexPtr = tm.get("switch_on");
	const GamesEngineeringBase::Image* helpButtonTexPtr = tm.get("help_button");

	//Tex load check
	if (playerTexPtr == nullptr)
	{
		std::cerr << "Failed to load Resources/IDLE.png" << std::endl;
		return 1;
	}

	//load map Tex
	map.setTileTexture(TileType::Wall, wallTexPtr);
	map.setTileTexture(TileType::Road, floorTexPtr);

	//load font
	BitmapFont font{};						
	font.load(tm.load("font","Resources/Font/SweetSunset+SweetSunrise/spritesheets/SweetSunset_bitmap_x2_rgba.png"));


	//create EnemyDefs
	EnemyDef def1 //balanced
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ enemyBalancedTexPtr },
		.maxHp{ 30 },
		.contactDamage{ 10 },
		.speed{ 100 },
		.score{ 10 }
	};
	EnemyDef def2 //fast but squishy
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ enemyFastTexPtr },
		.maxHp{ 15 },
		.contactDamage{ 5 },
		.speed{ 150 },
		.score {5}
	};
	EnemyDef def3 //slow but tanky
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ enemyTankTexPtr },
		.maxHp{ 80 },
		.contactDamage{ 20 },
		.speed{ 60 },
		.score{ 20 }
	};

	//create ProjectileDefs
	ProjectileDef bulletDef_warrior
	{
		.size{ 12.0f,12.0f },
		.tex{ bulletTexPtr },
		.speed{ 350.0f },
		.damage{ 5 },
		.lifetime{ 0.8f }
	};

	ProjectileDef bulletDef_ranger
	{
		.size{ 12.0f,12.0f },
		.tex{ bulletTexPtr },
		.speed{ 600.0f },
		.damage{ 12 },
		.lifetime{ 1.2f }
	};

	ProjectileDef bulletDef_mage
	{
		.size{ 12.0f,12.0f },
		.tex{ bulletTexPtr },
		.speed{ 400.0f },
		.damage{ 15 },
		.lifetime{ 1.5f }
	};

	//create MagicDefs
	ProjectileDef magicDef_mage
	{
		.size{ 20.0f,20.0f },
		.tex{ magicTexPtr },
		.speed{ 250.0f },
		.damage{ 25 },
		.lifetime{ 3.0f }
	};

	//create Herodefs
	HeroDef Warrior
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ warriorTexPtr },
		.maxHp{ 150 },
		.speed{ 180 },
		//J
		.meleeDamage{ 25 },
		.meleeBox{ 56.0f,56.0f },
		.meleeCooldown{ 0.4f },
		//K
		.shot{ &bulletDef_warrior },
		.shootCooldown{ 0.8f },
		//L
		.skill{ SkillType::Defence },
		.skillCooldown{ 8.0f },
		.skillDuration{ 4.0f },
		.skillMagnitude{ 0.5f },
		.magic{ nullptr }
	};

	HeroDef Ranger
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ rangerTexPtr },
		.maxHp{ 90 },
		.speed{ 230 },
		//J
		.meleeDamage{ 8 },
		.meleeBox{ 36.0f,36.0f },
		.meleeCooldown{ 0.5f },
		//K
		.shot{ &bulletDef_ranger },
		.shootCooldown{ 0.25f },
		//L
		.skill{ SkillType::Speed },
		.skillCooldown{ 6.0f },
		.skillDuration{ 3.0f },
		.skillMagnitude{ 2.0f },
		.magic{ nullptr }
	};

	HeroDef Mage
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ mageTexPtr },
		.maxHp{ 80 },
		.speed{ 200 },
		//J
		.meleeDamage{ 6 },
		.meleeBox{ 36.0f,36.0f },
		.meleeCooldown{ 0.6f },
		//K
		.shot{ &bulletDef_mage },
		.shootCooldown{ 0.5f },
		//L
		.skill{ SkillType::Magic },
		.skillCooldown{ 3.0f },
		.skillDuration{ 0.0f },
		.skillMagnitude{ 0 },
		.magic{ &magicDef_mage }
	};

	//since we use def in entities, def should be created before world

	//create World
	World world{};

	//lambda startLevel, so we can avoid passing in too many paras
	auto startLevel = [&](const HeroDef& hero, int level) -> Player*
		{
			world.clear();
			bool endless = (level == 1);
			if (!map.loadFromFile(endless ? "Resources/map2.txt" : "Resources/map1.txt"))
				std::cerr << "load map failure!";
			map.setWrap(endless);
			camera.setClamp(!endless);

			Player* playerPtr = new Player(Vec2{ 96.0f,96.0f }, & map, & input, & world, hero);
			world.add(playerPtr);
			world.add(new Spawner(Vec2{ 800.0f, 300.0f }, Vec2{ 112.0f, 96.0f }, spawnerNewTexPtr, 100, & map, & world, playerPtr, & def1, 5.0f)); // balanced
			world.add(new Spawner(Vec2{ 1500.0f, 900.0f }, Vec2{ 112.0f, 96.0f }, spawnerNewTexPtr, 80, & map, & world, playerPtr, & def2, 4.0f)); // fast
			world.add(new Spawner(Vec2{ 400.0f, 1200.0f }, Vec2{ 112.0f, 96.0f }, spawnerNewTexPtr, 150, & map, & world, playerPtr, & def3, 8.0f)); // tanky
			return playerPtr;
		};

	auto drawCentered = [&](const std::string& s, int y)->void
		{
			font.drawText(renderer, s, (camera.getScreenWidth() - font.measureText(s)) / 2, y);
		};

	//player pointer, decided by GameState::Menu now
	Player* playerPtr = nullptr;

	//set game state
	GameState state = GameState::Intro;
	int selectedHero = 0;
	int selectedLevel = 0;
	bool running{ true };//set game state running
	float elapsed = 0.0f;
	bool won = false;
	const char* helpLines[] = 
	{
		"CONTROLS",
		"W A S D  -  move",
		"J  -  melee attack",
		"K  -  ranged attack",
		"L  -  hero skill",
		"Warrior: damage shield",   
		"Ranger: speed dash",
		"Mage : homing magic",
		"",
		"GOAL",
		"Survive 120 seconds to win.",
		"Destroy spawners to stop enemies.",
		"",
		"Press Esc to return"
	};

	constexpr float kLevelDuration = 120.0f;
	constexpr int kHeroCount = 3;
	const HeroDef* heroes[kHeroCount] = { &Warrior, &Ranger, &Mage };
	const char* heroNames[kHeroCount] = { "Warrior", "Ranger", "Mage" };
	const char* levelNames[2] = { "Fixed", "Endless" };

	// main loop of the game
	while (running) 
	{
		//get dt
		float dt = timer.dt();

		//update input
		canvas.checkInput();
		input.update(canvas);

		//clear canvas
		renderer.clear();

		//switch state
		switch (state) {
		case GameState::Intro: 
		{
			drawCentered("Dungeon Adventure", 250);
			drawCentered("Press Enter", 400);
			if (input.wasPressed(VK_RETURN)) 
			{
				state = GameState::Menu;
			}
			break;
		}

		case GameState::Menu:
		{
			int listX = camera.getScreenWidth() / 2 - 60;
			int startY = 300;
			int lineH = 60;
			drawCentered("select your hero:", 200);
			drawCentered("W/S: select   A/D: level   Enter: start   H: help   Esc: quit", 600);

			for (int i = 0;i < kHeroCount;i++) {
				int y = startY + i * lineH;
				font.drawText(renderer, heroNames[i], listX, y);
				if (i == selectedHero) 
				{
					font.drawText(renderer, ">", listX - 40, y);
				}
			}

			drawCentered(std::string("Level: < ") + levelNames[selectedLevel] + " >", startY + kHeroCount * lineH + 30);

			if (input.wasPressed('S'))
				selectedHero = (selectedHero + 1) % kHeroCount;

			if (input.wasPressed('W'))
				selectedHero = (selectedHero + kHeroCount - 1) % kHeroCount;

			if (input.wasPressed('A'))
				selectedLevel = 1 - selectedLevel;

			if (input.wasPressed('D'))
				selectedLevel = 1 - selectedLevel;

			if (input.wasPressed('H')) 
				state = GameState::Help;

			if (input.wasPressed(VK_RETURN))
			{
				playerPtr = startLevel(*heroes[selectedHero], selectedLevel);
				elapsed = 0.0f;
				state = GameState::Play;
			}
				
			if (input.wasPressed(VK_ESCAPE))
				running = false;

			break;
		}

		case GameState::Help: 
		{
			for (int i = 0;i < sizeof(helpLines) / sizeof(helpLines[0]); i++)
			{
				font.drawText(renderer, helpLines[i], 10, 20 + i * 45);
			}
			if (input.wasPressed(VK_ESCAPE))
			{
				state = GameState::Menu;
			}
			break; 
		}

		case GameState::Play:
		{
			assert(playerPtr != nullptr);

			if (input.wasPressed(VK_ESCAPE))
			{
				state = GameState::Menu;
			}

			//before restrict dt,use raw dt to update fps
			fpscounter.update(dt);

			if (dt > 0.05f)
				dt = 0.05f;
			elapsed += dt;

			//movement of player
			world.update(dt);

			//camera follow and calculate screenCoordinate
			camera.follow(playerPtr->getCenter());

			//draw map
			map.draw(renderer, camera);

			//test: drawbound / draw attck box
			//Rect bounds = playerPtr->getBounds();
			//Vec2 leftp = Vec2{ camera.worldToScreen(Vec2{ bounds.x,bounds.y }) };
			//renderer.drawRect(leftp.x, leftp.y, bounds.w, bounds.h, 255, 0, 0);
			Rect attackBox = playerPtr->m_range;
			Vec2 leftp = Vec2{ camera.worldToScreen(Vec2{ attackBox.x,attackBox.y }) };
			renderer.drawRect(leftp.x, leftp.y, attackBox.w, attackBox.h, 255, 0, 0);

			//draw player
			world.draw(renderer, camera);

			//draw fps
			font.drawText(renderer, "FPS: " + std::to_string(fpscounter.getFps()), camera.getScreenWidth() - font.measureText("FPS: 1000") - 10, 10);

			//draw remaining time
			int remaining = static_cast<int>(kLevelDuration - elapsed);
			font.drawText(renderer, "Time: " + std::to_string(remaining), camera.getScreenWidth() - font.measureText("Time: 1000") - 10, 40);

			//draw Hp bar
			font.drawText(renderer, "^", 10, 10);
			renderer.drawRect(font.measureText("^") + 20, (41 - 10) / 2, 200, 30, 105, 105, 105);
			renderer.drawRect(font.measureText("^") + 20, (41 - 10) / 2, 200 * static_cast<float>(playerPtr->getHp()) / playerPtr->getMaxHp(), 30, 244, 128, 128);
			font.drawText(renderer, std::to_string(playerPtr->getHp()) + "/" + std::to_string(playerPtr->getMaxHp()), font.measureText("^") + 230, 9);
			
			//draw Score and Kills
			font.drawText(renderer, "Score: " + std::to_string(world.getScore()), 10, 40);
			font.drawText(renderer, "Kills: " + std::to_string(world.getKills()), 10, 70);

			//win judgement
			if(playerPtr->isDead())
			{
				won = false;
				state = GameState::Tally;
			}
			else 
			{
				if(elapsed >= kLevelDuration)
				{
					won = true;
					state = GameState::Tally;
				}
			}

			break;
		}

		case GameState::Tally: 
		{ 
			std::string result = won ? "VICTORY" : "DEFEATED";
			std::string heroLine = std::string("Hero: ") + heroNames[selectedHero];
			std::string timeLine = "Time survived: " + std::to_string(static_cast<int>(elapsed)) + " s";
			std::string killLine = "Kills: " + std::to_string(world.getKills());
			std::string scoreLine = "Score: " + std::to_string(world.getScore());
			std::string hint = "Press Enter to return to menu";
			drawCentered(result, 200);
			drawCentered(heroLine, 280);
			drawCentered(timeLine, 330);
			drawCentered(killLine, 380);
			drawCentered(scoreLine, 430);
			drawCentered(hint, 550);
			if (input.wasPressed(VK_RETURN))
			{
				state = GameState::Menu;
			}
			break; 
		}

		}

		//present the frame
		renderer.present();
	}
}