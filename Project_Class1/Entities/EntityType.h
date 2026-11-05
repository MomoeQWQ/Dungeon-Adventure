#pragma once

//EntityType enum class, used to identify the type of an entity in the game, including player, enemy, spawner, turret, pickup, spike, switch, door, and projectile
enum class EntityType 
{ 
	Player = 1, 
	Enemy, 
	Spawner, 
	Turret, 
	Pickup, 
	Spike, 
	Switch, 
	Door, 
	Projectile 
};