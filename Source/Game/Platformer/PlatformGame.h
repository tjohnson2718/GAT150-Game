#pragma once
#include "Framework/Game.h"
#include "Renderer/Renderer.h"

//inlude font and text

class PlatformGame : public kiko::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};

public:

	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(kiko::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0.0f;
	float m_spawnTime = 3.0f;
};

