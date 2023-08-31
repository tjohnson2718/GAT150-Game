#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

#include "Core/Core.h"

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool SpaceGame::Initialize()
{
	//Text
	m_font = GET_RESOURCE(kiko::Font, "spacegame/fonts/font.ttf", 24);

	// Audio
	kiko::g_audioSystem.AddAudio("shoot", "spacegame/audio/Laser2.wav");

	// Scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("spacegame/scenes/space_scene.json");
	m_scene->Initialize();

	// add events
	EVENT_SUBSCRIBE("OnAddPoints", SpaceGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDeath", SpaceGame::OnPlayerDeath);
	EVENT_SUBSCRIBE("OnBossDeath", SpaceGame::OnBossDeath);

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		m_scene->GetActorByName("Title")->active = true;
		m_scene->GetActorByName("Score")->active = false;
		m_scene->GetActorByName("GameOver")->active = false;
		m_scene->GetActorByName("Win")->active = false;
		m_scene->GetActorByName("PlayAgain")->active = false;
		m_scene->GetActorByName("Start")->active = true;

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName("Title")->active = false;
			m_scene->GetActorByName("Start")->active = false;
			m_scene->GetActorByName("Score")->active = true;
		}
		break;

	case SpaceGame::eState::StartGame:

		//Particle System
		m_score = 0;
		m_lives = 3;
		win = false;
		exists = false;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
		exists = false;

		{
			auto player = INSTANTIATE(Player, "Player");
			player->Initialize();
			m_scene->Add(std::move(player));

		}

		m_state = eState::Game;
		break;

	case SpaceGame::eState::Game:
		m_spawnTimer += dt;

		//Emitter
		{
			if (kiko::g_inputSystem.GetKeyDown(SDL_BUTTON_LEFT))
			{
				kiko::EmitterData data;
				data.burst = true;
				data.burstCount = 100;
				data.spawnRate = 200;
				data.angle = 0;
				data.angleRange = kiko::Pi;
				data.lifetimeMin = 0.5f;
				data.lifetimeMin = 1.5f;
				data.speedMin = 50;
				data.speedMax = 250;
				data.damping = 0.5f;
				data.color = kiko::Color{ 1, 0, 0, 1 };
				kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0, 1 };
				auto emitter = std::make_unique<kiko::Emitter>(transform, data);
				emitter->lifespan = 1.0f;
				m_scene->Add(std::move(emitter));
			}
		}

		if (m_spawnTimer >= m_spawnTime && exists == false)
		{
			auto enemy = INSTANTIATE(Enemy, "Enemy");
			enemy->Initialize();
			m_scene->Add(std::move(enemy));

			m_spawnTimer = 0;
		}

		if (m_score >= 100 && exists == false)
		{
			auto boss = INSTANTIATE(Boss, "Boss");
			boss->Initialize();
			m_scene->Add(std::move(boss));

			exists = true;
		}
		
		break;

	case SpaceGame::eState::PlayerDead:
		if (m_lives <= 0 || win == true)
		{
			m_state = eState::GameOver;
		}

		else m_state = eState::StartLevel;

		break;

	case SpaceGame::eState::GameOver:
		if (win == true)
		{
			m_scene->GetActorByName("Win")->active = true;
			m_scene->GetActorByName("PlayAgain")->active = true;
			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_P))
			{
				m_state = eState::Title;
			}
		}
		else
		{
			m_scene->GetActorByName("GameOver")->active = true;
		}
		
		break;

	default:
		break;
	}

	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);

	//m_scoreText->Draw(renderer, 40, 40);
}

void SpaceGame::OnAddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);

	std::cout << m_score << std::endl;
}

void SpaceGame::OnPlayerDeath(const kiko::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDead;
}

void SpaceGame::OnBossDeath(const kiko::Event& event)
{
	win = true;
	m_state = eState::PlayerDead;
}
