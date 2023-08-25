#include "PlatformGame.h"
#include "Renderer/Renderer.h"
#include "Core/Core.h" 
#include"Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"

#include "Physics/PhysicsSystem.h"

#include <iostream> 
#include <vector>
#include <thread>
#include <map>

using namespace std;

class Star
{
public:
	
	void Update()
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};

int main(int argc, char* argv[])
{
	kiko::Factory::Instance().Register<kiko::SpriteComponent>("SpriteComponent");

	INFO_LOG("Initialize Engine...");


	kiko::MemoryTracker::Initialize();
	std::unique_ptr<int> up = std::make_unique<int>(10);

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	//our window setup
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();




	//Create the game
	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
//	game->Initialize();


	// main game loop
	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();

		kiko::g_audioSystem.Update();

		kiko::g_particleSystem.Update(1.0f);

		//kiko::PhysicsSystem.Instance().Update(kiko::g_time.GetDeltaTime());

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::g_audioSystem.PlayOneShot("shoot");
		}

		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//game->Update(kiko::g_time.GetDeltaTime());

		kiko::g_renderer.SetColor(0, 0, 0, 0); //sets color to black
		kiko::g_renderer.BeginFrame(); //clears the screen, allows for less static
		//draw
		game->Draw(kiko::g_renderer);

		//kiko::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		kiko::g_particleSystem.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	return 0;
}
