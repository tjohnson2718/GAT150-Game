#pragma once
#include "Framework/Game.h"
#include "Renderer/Renderer.h"
#include "Framework/Event/EventManager.h"

//inlude font and text

class SpaceGame : public kiko::Game, kiko::IEventListener
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
	void OnAddPoints(const kiko::Event& event);
	void OnPlayerDead(const kiko::Event& event);

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0.0f;
	float m_spawnTime = 3.0f;

	float m_statTimer = 0;
	float m_gameTimer = 0;

	std::shared_ptr<kiko::Font> m_font;
	std::unique_ptr<kiko::Text> m_scoreText;
	std::unique_ptr<kiko::Text> m_titleText;
};
