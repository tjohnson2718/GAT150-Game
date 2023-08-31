#include "PlatformGame.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool PlatformGame::Initialize()
{
	// Audio
	//kiko::g_audioSystem.AddAudio("shoot", "Laser2.wav");

	// Scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("Platformer/Scenes/platformer_scene.json");
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
	{
		//auto actor = INSTANTIATE(Actor, "Crate");
		//actor->transform.position = { kiko::randomf(kiko::g_renderer.GetWidth(), 100) };
		//actor->Initialize();
		//m_scene->Add(std::move(actor));
	}
		//m_scene->GetActorByName("Title")->active = true;

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			//m_scene->GetActorByName("Title")->active = false;
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

		m_state = eState::Game;
		break;

	case PlatformGame::eState::Game:
		m_spawnTimer += dt;

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
