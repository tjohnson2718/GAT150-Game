#include "PlatformGame.h"

#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool PlatformGame::Initialize()
{
	// Audio
	kiko::g_audioSystem.AddAudio("shoot", "Laser2.wav");

	// Scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scenes/space_scene.json");
	m_scene->Initialize();

	return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
	switch (m_state)
	{
	case PlatformGame::eState::Title:
		m_scene->GetActorByName("Title")->active = true;

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName("Title")->active = false;
			//m_scene->GetActorByName <kiko::Actor >("Background")->active;
		}
		break;

	case PlatformGame::eState::StartGame:

		//Particle System
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll();

		{

		}

		m_state = eState::Game;
		break;

	case PlatformGame::eState::Game:
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

		if (m_spawnTimer >= m_spawnTime)
		{
		}

		break;

	case PlatformGame::eState::PlayerDead:
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::StartLevel;

		if (m_lives == 0)
		{
			m_state = eState::GameOver;
		}
		else
		{
			m_state = eState::StartLevel;
		}

		break;

	case PlatformGame::eState::GameOver:
		break;

	default:
		break;
	}

	m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
	m_scene->Draw(renderer);
}
