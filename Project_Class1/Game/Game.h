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
	Game();
	~Game();

private:
	static constexpr float kLevelDuration = 120.0f;
	static constexpr int kHeroCount = 3;
	static const HeroDef* heroes[kHeroCount] = { &Warrior, &Ranger, &Mage };
	static const char* heroNames[kHeroCount] = { "Warrior", "Ranger", "Mage" };
	static const char* levelNames[2] = { "Fixed", "Endless" };

	GamesEngineeringBase::Window m_canvas;
	GamesEngineeringBase::Timer m_timer;
	Input m_input; 
	Renderer m_renderer;
	FpsCounter m_fps;

	TextureManager m_tm; 
	BitmapFont m_font;

	Tilemap m_map; 
	Camera m_camera;

	EnemyDef m_enemyDefs[3]; 
	ProjectileDef m_shotDefs[3]; 
	ProjectileDef m_magicDef; 
	HeroDef m_heroDefs[kHeroCount];

	World m_world;

	GameState m_state; 
	int m_selectedHero, m_selectedLevel; 
	bool m_running, m_won; 
	float m_elapsed; 
	Player* m_player{ nullptr };
};

Game::Game()
{
}

Game::~Game()
{
}