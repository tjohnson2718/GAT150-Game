#include "Renderer/Renderer.h"
#include "Core/Core.h" 
#include"Input/InputSystem.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"


#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"

#include "Physics/PhysicsSystem.h"

#include <iostream> 
#include <vector>
#include <thread>
#include <map>
#include <functional>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

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
	INFO_LOG("Initialize Engine...")

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
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	//load ship
	//kiko::res_t<kiko::Texture>texture = kiko::g_resources.Get<kiko::Texture>("ship.png", kiko::g_renderer);
 	

	vector<Star> stars; 

	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(0.7f, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	// main game loop
	bool quit = false;
	while (!quit)
	{
 		kiko::g_time.Tick();

		kiko::g_audioSystem.Update();

		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());

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

		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		game->Update(kiko::g_time.GetDeltaTime());
		
		kiko::g_renderer.SetColor(0, 0, 0, 0); //sets color to black
		kiko::g_renderer.BeginFrame(); //clears the screen, allows for less static
		//draw
		kiko::g_particleSystem.Draw(kiko::g_renderer);
		game->Draw(kiko::g_renderer);

		

		kiko::g_renderer.EndFrame();
	}

	stars.clear();

	return 0;
}
