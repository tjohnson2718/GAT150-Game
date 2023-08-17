#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Core/Core.h"

#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

bool SpaceGame::Initialize()
{
	//Text
	//m_font = GET_RESOURCE(kiko::Font, "font.ttf", 24);
	std::shared_ptr<kiko::Font> font = std::make_shared<kiko::Font>("font.ttf", 24);
	std::unique_ptr<kiko::Text> text = std::make_unique<kiko::Text>(font);
	text->Create(kiko::g_renderer, "NEUMONT", kiko::Color{ 1, 1, 1, 1 });
	
	//replace m_font with code


	// Audio
	kiko::g_audioSystem.AddAudio("shoot", "Laser2.wav");

	// Scene
	m_scene = std::make_unique<kiko::Scene>();

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
		
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;

	case SpaceGame::eState::StartGame:

		//Particle System
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();

		{
			// create player
			auto player = std::make_unique<Player>(20.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 1 });
			player->tag = "Player";
			player->m_game = this;
			
			////create components

			//model component
			auto renderComponent = CREATE_CLASS(RenderComponent); //std::make_unique<kiko::SpriteComponent>();
			renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer); //kiko::g_resources.Get<kiko::Texture>("ship.png", kiko::g_renderer);
			player->AddComponent(std::move(renderComponent));

			//physics component
			auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent); //std::make_unique<kiko::EnginePhysicsComponent>();
			physicsComponent->m_damping = 0.9f;
			player->AddComponent(std::move(physicsComponent));

			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent); //std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			player->Initialize();
			m_scene->Add(std::move(player));
			// do this same thing for the enemy
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

		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(4.0f, 7.0f), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 3.0f });
			enemy->tag = "Enemy";
			enemy->m_game = this;

			auto renderComponent = kiko::Factory::Instance().Create<kiko::SpriteComponent>("SpriteComponent");
			renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "ship.png", kiko::g_renderer); 
			enemy->AddComponent(std::move(renderComponent));

			auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));

			enemy->Initialize();
			m_scene->Add(move(enemy));
		}

		break;

	case SpaceGame::eState::PlayerDead:
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

	case SpaceGame::eState::GameOver:
		break;

	default:
		break;
	}

	//m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 });
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		//m_titleText->Draw(renderer, 400, 300);
	}

	//m_scoreText->Draw(renderer, 40, 40)
	m_scene->Draw(renderer);
}
