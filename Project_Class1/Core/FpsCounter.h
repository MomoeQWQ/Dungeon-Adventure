#pragma once


//FPS counter class, responsible for calculating and providing the current frames per second (FPS) of the game
class FpsCounter
{
public:
	FpsCounter() = default;
	void update(float dt) 
	{
		m_elapsed += dt;
		m_frames += 1;
		if (m_elapsed >= 0.5f)
		{
			m_fps = static_cast<int>(m_frames / m_elapsed);
			m_frames = 0;
			m_elapsed = 0.0f;
		}
	}

	int getFps() const
	{
		return m_fps;
	}

private:
	int m_frames{};
	float m_elapsed{};
	int m_fps{};
};
