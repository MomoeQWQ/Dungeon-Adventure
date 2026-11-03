#pragma once
#include "../GamesEngineeringBase.h"
#include "../Core/DynamicArray.h"
#include "../Core/Vec2.h"
#include "../Core/FpsCounter.h"
#include "../Render/Renderer.h"
#include "../Render/TextureManager.h"
#include "../Render/Camera.h"
#include "../Render/BitmapFont.h"
#include "Input.h"
#include "World.h"
#include "Tilemap.h"
#include "GameState.h"
#include "../Entities/Player.h"
#include "../Entities/EnemyDef.h"
#include "../Entities/Enemy.h"
#include "../Entities/Spawner.h"
#include "../Entities/ProjectileDef.h"
#include "../Entities/HeroDef.h"
#include <iostream>
#include <string>

class Game
{
public:
	Game() = default;
	Game(const Game& source) = delete;
	Game& operator=(const Game& source) = delete;

	bool init();
	void run();

private:
	static constexpr float kLevelDuration = 120.0f;
	static constexpr int kHeroCount = 3;
	static constexpr int kScreenW = 1024;//default to init camera,and we'll update it when loading map file
	static constexpr int kScreenH = 768;;
	static constexpr const char* heroNames[kHeroCount] = { "Warrior", "Ranger", "Mage" };
	static constexpr const char* levelNames[2] = { "Fixed", "Endless" };

	//engine & render & world
	GamesEngineeringBase::Window m_canvas;
	GamesEngineeringBase::Timer m_timer;
	Input m_input{};
	Renderer m_renderer{m_canvas};
	FpsCounter m_fps{};

	TextureManager m_tm{};
	BitmapFont m_font{};

	Tilemap m_map{ 64,48,Vec2{ 32.0f,32.0f } };//default tilemap

	//Camera init(int worldWidth, int worldHeight,int screenWidth,int screenHeight)
	//We need to create camera after map cuz it relies on the latter one
	//since now we haven't init the map, use k-numbers to init camera
	Camera m_camera{ kScreenW, kScreenH, static_cast<int>(m_canvas.getWidth()), static_cast<int>(m_canvas.getHeight()) };

	EnemyDef m_enemyDefs[3]; 
	ProjectileDef m_shotDefs[3]; 
	ProjectileDef m_magicDef; 
	HeroDef m_heroDefs[kHeroCount];
	ProjectileDef m_enemyShotDef{};

	//world must be defined after def, cuz we have pointers linked to entities in def
	World m_world{};

	//Game
	GameState m_state{ GameState::Intro };
	int m_selectedHero{ 0 };
	int m_selectedLevel{ 0 };
	bool m_running{true};
	bool m_won{ false };
	float m_elapsed{ 0.0f };
	Player* m_player{ nullptr };

	//load Game(for S/L)
	bool loadGame(const std::string& path);

	//helper functions
	void loadTextures();
	void setupDefs();
	bool prepareLevel(int level);
	Player* startLevel(const HeroDef& hero, int level);
	void drawCentered(const std::string& s, int y);
	void drawBar(int x, int y, int w, int h, float cur, float max, unsigned char r, unsigned char g, unsigned char b);
	void drawHud();
	void updateIntro();
	void updateMenu();
	void updateHelp();
	void updatePlay(float dt);
	void updateTally();
	bool saveGame(const std::string& path) const;
	void writeEntity(std::ostream& out, const Entity& e) const;
};