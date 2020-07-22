// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "core.h"
#include "Math/Math2.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include <vector>
#include <string>
#include <list>
#include <vector>

const size_t NUM_POINTS = 40;
float thrust = 500.0f;
nc::Vector2 velocity;

float t{ 0 };

float frametime;
float spawntimer{ 0 };
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

std::list<nc::Actor*> actors;

nc::Scene scene;
nc::ParticleSystem particleSystem;




bool Update(float dt) // delta time (60fps -> 1 / 60 = .016)
{
	frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	spawntimer += dt;
	if (spawntimer >= 3.0f)
	{
		spawntimer = 0.0f;
		//add enemy to scene

		nc::Actor* actor = new Enemy;
		actor->Load("enemy.txt");
		dynamic_cast<Enemy*>(actor)->SetTarget(scene.GetActor<Player>());
		actor->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<Enemy*>(actor)->SetThrust(nc::random(50, 100));

		scene.AddActor(actor);

	}

	
	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::blue, nc::Color::red };
		nc::Color color = colors[rand() % 3]; // 0, 1, 2

		g_particleSystem.Create({ x,y }, 0, 180, 30, color, 1, 100, 200);
	}

	g_particleSystem.Update(dt);
	scene.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f; // 0 - 2

	nc::Color c = nc::Lerp(nc::Color{ 0, 0, 1 }, nc::Color{ 1, 0, 0 }, v);
	graphics.SetColor(c);

	nc::Vector2 p = nc::Lerp(nc::Vector2{ 400,300 }, nc::Vector2{ 400,100 }, v);
	//graphics.DrawString(p.x, p.y, "Last Starfighter");

	//if (gameOver) graphics.DrawString(400, 300, "Game Over");

	scene.Draw(graphics);
	g_particleSystem.Draw(graphics);
}

int main() 
{ 
	scene.Startup();
	g_particleSystem.Startup();

	nc::Actor* player = new Player;
	player->Load("player.txt");
	scene.AddActor(player);

	for (int i = 0; i < 10; i++) 
	{
		nc::Actor* enemy = new Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<Enemy*>(enemy)->SetThrust(nc::random(50, 100));
		
		scene.AddActor(enemy);
	}
	
	char name[] = "New Super Shapey Bros WiiU & Knuckles Featuring Dante From The Devil May Cry Series"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown();

	scene.Shutdown(); 
	g_particleSystem.Shutdown();
}

