#pragma once
#include "../Core/DynamicArray.h"
#include "../Entities/Entity.h"

class Renderer;
class Camera;

class World
{
public:
	World() = default;
	World(const World& source) = delete;
	World& operator=(const World& source) = delete;
	~World();

	void add(Entity* e);
	void update(float dt);
	void draw(Renderer&, const Camera&) const;
	int getCount() const;

private:
	DynamicArray<Entity*> m_entities{};

	void removeDead();//World determines when to remove
};
