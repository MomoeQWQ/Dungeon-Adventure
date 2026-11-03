#include "Game.h"
#include "../Entities/Turret.h"
#include "../Entities/SpikeTrap.h"
#include "../Entities/Pickup.h"
#include <cassert>

namespace 
{ 
	constexpr const char* kHelpLines[] = 
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
}

void Game::loadTextures() 
{
	//texture manager init
	m_tm.load("player", "Resources/IDLE.png");
	m_tm.load("bullet", "Resources/bullet.png");
	m_tm.load("magicbullet", "Resources/magic.png");
	m_tm.load("enemy_balanced", "Resources/enemy_balanced.png");
	m_tm.load("enemy_fast", "Resources/enemy_fast.png");
	m_tm.load("enemy_tank", "Resources/enemy_tank.png");
	m_tm.load("spawner_new", "Resources/spawner.png");
	m_tm.load("hero_warrior", "Resources/hero_warrior.png");
	m_tm.load("hero_ranger", "Resources/hero_ranger.png");
	m_tm.load("hero_mage", "Resources/hero_mage.png");
	m_tm.load("tile_floor", "Resources/tile_floor.png");
	m_tm.load("tile_wall", "Resources/tile_wall.png");
	m_tm.load("enemy_bullet", "Resources/enemy_bullet.png");
	m_tm.load("potion_hp", "Resources/potion_hp.png");
	m_tm.load("potion_mp", "Resources/potion_mp.png");
	m_tm.load("key", "Resources/key.png");
	m_tm.load("door_closed", "Resources/door_closed.png");
	m_tm.load("door_open", "Resources/door_open.png");
	m_tm.load("trap_spikes", "Resources/trap_spikes.png");
	m_tm.load("trap_turret", "Resources/trap_turret.png");
	m_tm.load("switch_off", "Resources/switch_off.png");
	m_tm.load("switch_on", "Resources/switch_on.png");
	m_tm.load("help_button", "Resources/help_button.png");

	//Tex load check(haven't completed all, too long......)
	if (m_tm.get("player") == nullptr)
	{
		std::cerr << "Failed to load Resources/IDLE.png" << std::endl;
		return;
	}

	//load map Tex
	m_map.setTileTexture(TileType::Wall, m_tm.get("tile_wall"));
	m_map.setTileTexture(TileType::Road, m_tm.get("tile_floor"));

	//load font
	m_font.load(m_tm.load("font", "Resources/Font/SweetSunset+SweetSunrise/spritesheets/SweetSunset_bitmap_x2_rgba.png"));
}

void Game::setupDefs() 
{
	//create EnemyDefs
	m_enemyDefs[0] = EnemyDef //balanced
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ m_tm.get("enemy_balanced") },
		.maxHp{ 30 },
		.contactDamage{ 10 },
		.speed{ 100 },
		.score{ 10 }
	};
	m_enemyDefs[1] = EnemyDef //fast but squishy
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ m_tm.get("enemy_fast") },
		.maxHp{ 15 },
		.contactDamage{ 5 },
		.speed{ 150 },
		.score{ 5 }
	};
	m_enemyDefs[2] = EnemyDef //slow but tanky
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ m_tm.get("enemy_tank") },
		.maxHp{ 80 },
		.contactDamage{ 20 },
		.speed{ 60 },
		.score{ 20 }
	};

	//create ProjectileDefs
	m_shotDefs[0] = ProjectileDef
	{
		.size{ 12.0f,12.0f },
		.tex{ m_tm.get("bullet") },
		.speed{ 350.0f },
		.damage{ 5 },
		.lifetime{ 0.8f }
	};

	m_shotDefs[1] = ProjectileDef
	{
		.size{ 12.0f,12.0f },
		.tex{ m_tm.get("bullet") },
		.speed{ 600.0f },
		.damage{ 12 },
		.lifetime{ 1.2f }
	};

	m_shotDefs[2] = ProjectileDef
	{
		.size{ 12.0f,12.0f },
		.tex{ m_tm.get("bullet") },
		.speed{ 400.0f },
		.damage{ 15 },
		.lifetime{ 1.5f }
	};

	//create MagicDefs
	m_magicDef = ProjectileDef
	{
		.size{ 20.0f,20.0f },
		.tex{ m_tm.get("magicbullet") },
		.speed{ 250.0f },
		.damage{ 25 },
		.lifetime{ 3.0f }
	};

	//create enemy's shot
	m_enemyShotDef = ProjectileDef
	{
		.size{ 12.0f,12.0f },
		.tex{ m_tm.get("enemy_bullet") },
		.speed{ 250.0f },
		.damage{ 8 },
		.lifetime{ 3.0f }
	};

	//create Herodefs
	m_heroDefs[0] = HeroDef
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ m_tm.get("hero_warrior") },
		.maxHp{ 150 },
		.speed{ 180 },
		//J
		.meleeDamage{ 25 },
		.meleeBox{ 56.0f,56.0f },
		.meleeCooldown{ 0.4f },
		//K
		.shot{ &m_shotDefs[0] },
		.shootCooldown{ 0.8f },
		//L
		.skill{ SkillType::Defence },
		.skillCooldown{ 8.0f },
		.skillDuration{ 4.0f },
		.skillMagnitude{ 0.5f },
		.magic{ nullptr },
		.maxMana{50.0f},
		.skillManaCost{5.0f},
		.manaRegen{2.0f}
	};

	m_heroDefs[1] = HeroDef
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ m_tm.get("hero_ranger") },
		.maxHp{ 90 },
		.speed{ 230 },
		//J
		.meleeDamage{ 8 },
		.meleeBox{ 36.0f,36.0f },
		.meleeCooldown{ 0.5f },
		//K
		.shot{ &m_shotDefs[1] },
		.shootCooldown{ 0.25f },
		//L
		.skill{ SkillType::Speed },
		.skillCooldown{ 6.0f },
		.skillDuration{ 3.0f },
		.skillMagnitude{ 2.0f },
		.magic{ nullptr },
		.maxMana{ 70.0f },
		.skillManaCost{ 10.0f },
		.manaRegen{ 3.0f }
	};

	m_heroDefs[2] = HeroDef
	{
		.size{ 112.0f,96.0f },
		.hitboxOffset{ 39.0f,49.0f },
		.hitboxSize{ 31.0f,37.0f },
		.tex{ m_tm.get("hero_mage") },
		.maxHp{ 80 },
		.speed{ 200 },
		//J
		.meleeDamage{ 6 },
		.meleeBox{ 36.0f,36.0f },
		.meleeCooldown{ 0.6f },
		//K
		.shot{ &m_shotDefs[2] },
		.shootCooldown{ 0.5f },
		//L
		.skill{ SkillType::Magic },
		.skillCooldown{ 3.0f },
		.skillDuration{ 0.0f },
		.skillMagnitude{ 0 },
		.magic{ &m_magicDef },
		.maxMana{ 100.0f },
		.skillManaCost{ 10.0f },
		.manaRegen{ 5.0f }
	};

}

Player* Game::startLevel(const HeroDef& hero, int level)
{
	m_world.clear();
	bool endless = (level == 1);
	if (!m_map.loadFromFile(endless ? "Resources/map2.txt" : "Resources/map1.txt"))
		std::cerr << "load map failure!";
	m_map.setWrap(endless);
	m_camera.setClamp(!endless);

	Player* playerPtr = new Player(Vec2{ 96.0f,96.0f }, &m_map, &m_input, &m_world, hero);

	m_world.add(new SpikeTrap(Vec2{ 200.0f,200.0f }, Vec2{ 32.0f, 32.0f }, m_tm.get("trap_spikes"), playerPtr, 10, true));
	m_world.add(new Pickup(Vec2{ 360.0f,160.0f }, Vec2{ 16.0f, 16.0f }, m_tm.get("potion_hp"), PickupType::Health, 30, playerPtr));
	m_world.add(new Pickup(Vec2{ 220.0f,160.0f }, Vec2{ 16.0f, 16.0f }, m_tm.get("potion_mp"), PickupType::Mana, 30, playerPtr));
	m_world.add(new Pickup(Vec2{ 280.0f,160.0f }, Vec2{ 16.0f, 16.0f }, m_tm.get("key"), PickupType::Key, 30, playerPtr));
	m_world.add(playerPtr);
	m_world.add(new Spawner(Vec2{ 800.0f, 300.0f }, Vec2{ 112.0f, 96.0f }, m_tm.get("spawner_new"), 100, &m_map, &m_world, playerPtr, &m_enemyDefs[0], 5.0f)); // balanced
	m_world.add(new Spawner(Vec2{ 1500.0f, 900.0f }, Vec2{ 112.0f, 96.0f }, m_tm.get("spawner_new"), 80, &m_map, &m_world, playerPtr, &m_enemyDefs[1], 4.0f)); // fast
	m_world.add(new Spawner(Vec2{ 400.0f, 1200.0f }, Vec2{ 112.0f, 96.0f }, m_tm.get("spawner_new"), 150, &m_map, &m_world, playerPtr, &m_enemyDefs[2], 8.0f)); // tanky
	m_world.add(new Turret(Vec2{ 300.0f,300.0f }, Vec2{ 32.0f, 32.0f }, m_tm.get("trap_turret"), 60, &m_map, &m_world, &m_enemyShotDef, 1.5, 160000, playerPtr->getId()));
	return playerPtr;
};

void Game::drawCentered(const std::string& s, int y)
{
	m_font.drawText(m_renderer, s, (m_camera.getScreenWidth() - m_font.measureText(s)) / 2, y);
};

void Game::drawHud()
{
	if (m_player == nullptr)
		return;

	//draw remaining time
	int remaining = static_cast<int>(kLevelDuration - m_elapsed);
	m_font.drawText(m_renderer, "Time: " + std::to_string(remaining), m_camera.getScreenWidth() - m_font.measureText("Time: 1000") - 10, 40);

	//draw Hp bar
	m_font.drawText(m_renderer, "^", 10, 10);
	m_renderer.drawRect(m_font.measureText("^") + 20, (41 - 10) / 2, 200, 30, 105, 105, 105);
	m_renderer.drawRect(m_font.measureText("^") + 20, (41 - 10) / 2, 200 * static_cast<float>(m_player->getHp()) / m_player->getMaxHp(), 30, 244, 128, 128);
	m_font.drawText(m_renderer, std::to_string(m_player->getHp()) + "/" + std::to_string(m_player->getMaxHp()), m_font.measureText("^") + 230, 9);

	//draw Score and Kills
	m_font.drawText(m_renderer, "Score: " + std::to_string(m_world.getScore()), 10, 40);
	m_font.drawText(m_renderer, "Kills: " + std::to_string(m_world.getKills()), 10, 70);
}

//init the game:read from files, create window, refresh camera, load tex, create entities' defs
bool Game::init() 
{
	//load map from file
	if (!m_map.loadFromFile("Resources/map1.txt"))
		return false;

	//create window
	m_canvas.create(1024, 768, "Dungeon Adventure");    

	//reload Camera since mapW or mapH may differ from k-nums
	m_camera = Camera (m_map.getPixelWidth(), m_map.getPixelHeight(), static_cast<int>(m_canvas.getWidth()), static_cast<int>(m_canvas.getHeight()));

	//load textures
	loadTextures();

	//create defs
	setupDefs();

	return true;
}


void Game::updateIntro()
{
	drawCentered("Dungeon Adventure", 250);
	drawCentered("Press Enter", 400);
	if (m_input.wasPressed(VK_RETURN))
	{
		m_state = GameState::Menu;
	}
}

void Game::updateMenu() 
{
	int listX = m_camera.getScreenWidth() / 2 - 60;
	int startY = 300;
	int lineH = 60;
	drawCentered("select your hero:", 200);
	drawCentered("W/S: select   A/D: level   Enter: start   H: help   Esc: quit", 600);

	for (int i = 0;i < kHeroCount;i++) {
		int y = startY + i * lineH;
		m_font.drawText(m_renderer, heroNames[i], listX, y);
		if (i == m_selectedHero)
		{
			m_font.drawText(m_renderer, ">", listX - 40, y);
		}
	}

	drawCentered(std::string("Level: < ") + levelNames[m_selectedLevel] + " >", startY + kHeroCount * lineH + 30);

	if (m_input.wasPressed('S'))
		m_selectedHero = (m_selectedHero + 1) % kHeroCount;

	if (m_input.wasPressed('W'))
		m_selectedHero = (m_selectedHero + kHeroCount - 1) % kHeroCount;

	if (m_input.wasPressed('A'))
		m_selectedLevel = 1 - m_selectedLevel;

	if (m_input.wasPressed('D'))
		m_selectedLevel = 1 - m_selectedLevel;

	if (m_input.wasPressed('H'))
		m_state = GameState::Help;

	if (m_input.wasPressed(VK_RETURN))
	{
		m_player = startLevel(m_heroDefs[m_selectedHero], m_selectedLevel);
		m_elapsed = 0.0f;
		m_state = GameState::Play;
	}

	if (m_input.wasPressed(VK_ESCAPE))
		m_running = false;
}

void Game::updateHelp() 
{
	for (int i = 0;i < sizeof(kHelpLines) / sizeof(kHelpLines[0]); i++)
	{
		m_font.drawText(m_renderer, kHelpLines[i], 10, 20 + i * 45);
	}
	if (m_input.wasPressed(VK_ESCAPE))
	{
		m_state = GameState::Menu;
	}
}

void Game::updatePlay(float dt)
{
	assert(m_player != nullptr);

	if (m_input.wasPressed(VK_ESCAPE))
	{
		m_state = GameState::Menu;
	}

	//before restrict dt,use raw dt to update fps
	m_fps.update(dt);

	if (dt > 0.05f)
		dt = 0.05f;
	m_elapsed += dt;

	//movement of player
	m_world.update(dt);

	//camera follow and calculate screenCoordinate
	m_camera.follow(m_player->getCenter());

	//draw map
	m_map.draw(m_renderer, m_camera);

	//test: drawbound / draw attck box
	//Rect bounds = playerPtr->getBounds();
	//Vec2 leftp = Vec2{ camera.worldToScreen(Vec2{ bounds.x,bounds.y }) };
	//renderer.drawRect(leftp.x, leftp.y, bounds.w, bounds.h, 255, 0, 0);
	//Rect attackBox = m_player->m_range;
	//Vec2 leftp = Vec2{ m_camera.worldToScreen(Vec2{ attackBox.x,attackBox.y }) };
	//m_renderer.drawRect(leftp.x, leftp.y, attackBox.w, attackBox.h, 255, 0, 0);

	//draw player
	m_world.draw(m_renderer, m_camera);

	//draw Hud
	drawHud();

	//win judgement
	if (m_player->isDead())
	{
		m_won = false;
		m_state = GameState::Tally;
	}
	else
	{
		if (m_elapsed >= kLevelDuration)
		{
			m_won = true;
			m_state = GameState::Tally;
		}
	}
}

void Game::updateTally()
{
	std::string result = m_won ? "VICTORY" : "DEFEATED";
	std::string heroLine = std::string("Hero: ") + heroNames[m_selectedHero];
	std::string timeLine = "Time survived: " + std::to_string(static_cast<int>(m_elapsed)) + " s";
	std::string killLine = "Kills: " + std::to_string(m_world.getKills());
	std::string scoreLine = "Score: " + std::to_string(m_world.getScore());
	std::string hint = "Press Enter to return to menu";
	drawCentered(result, 200);
	drawCentered(heroLine, 280);
	drawCentered(timeLine, 330);
	drawCentered(killLine, 380);
	drawCentered(scoreLine, 430);
	drawCentered(hint, 550);
	if (m_input.wasPressed(VK_RETURN))
	{
		m_state = GameState::Menu;
	}
}


//main loop,including checking inputs, cal dt/fps, clear/draw, game state switch and update
void Game::run()
{
	// main loop of the game
	while (m_running)
	{
		//get dt
		float dt = m_timer.dt();

		//update input
		m_canvas.checkInput();
		m_input.update(m_canvas);

		//clear canvas
		m_renderer.clear();

		//switch state
		switch (m_state) {
		case GameState::Intro:
		{
			updateIntro();
			break;
		}

		case GameState::Menu:
		{
			updateMenu();
			break;
		}

		case GameState::Help:
		{
			updateHelp();
			break;
		}

		case GameState::Play:
		{
			updatePlay(dt);
			break;
		}

		case GameState::Tally:
		{
			updateTally();
			break;
		}

		}

		//draw fps(we need fps throughout the game, so it in not included in the function drawHud)
		//instead, it's here
		m_font.drawText(m_renderer, "FPS: " + std::to_string(m_fps.getFps()), m_camera.getScreenWidth() - m_font.measureText("FPS: 1000") - 10, 10);

		//present the frame
		m_renderer.present();
	}
}

