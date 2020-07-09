// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "core.h"
#include "Math/Math2.h"
#include "Math/Random.h"
//#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Object/Actor.h"
#include <vector>
#include <string>

const size_t NUM_POINTS = 40;
float speed = 300.0f;

std::vector<nc::Vector2> points = { { 3, -3 }, { 3, 3 }, { -3, 3 }, { -3, -3 }, {3 , -3}, {0, -10}, {-3, -3} };
nc::Color color{0, 1, 0};
nc::Shape shape;
//nc::Shape shape(points, color);

nc::Transform transform{ { 400, 300 }, 4, 0 };

float t{ 0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

nc::Actor player;
nc::Actor enemy;


bool Update(float dt) // delta time (60fps -> 1 / 60 = .016)
{
	
	DWORD time = GetTickCount();
	deltaTime = time - prevTime; //current frame time - previous frame time
	prevTime = time;

	t = t + dt * 5.0f;

	frametime = dt;
	roundTime += dt;

	if (roundTime >= 5.0f) gameOver = true;

	if (gameOver) dt = 0;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	//nc::Vector2 target = nc::Vector2{ x, y };
	//nc::Vector2 direction = target - position; //(head <- tail)
	//direction.Normalize();

	nc::Vector2 force;
	if (Core::Input::IsPressed(Core::Input::KEY_UP))
	{
		force = nc::Vector2::forward * speed * dt;
	}
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, transform.angle);
	transform.position = transform.position + direction;

	if (Core::Input::IsPressed(Core::Input::KEY_LEFT))
	{
		transform.angle = transform.angle - (nc::DegreesToRadians(360.0f) * dt);
	}
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT))
	{
		transform.angle = transform.angle + (nc::DegreesToRadians(360.0f) * dt);
	}

	transform.position = nc::Clamp(transform.position, { 0,0 }, { 800,600 });

	//transform.position.x = nc::Clamp(transform.position.x, 0.0f, 800.0f);
	//transform.position.y = nc::Clamp(transform.position.y, 0.0f, 600.0f);


	//if (Core::Input::IsPressed(Core::Input::KEY_LEFT))
	//{
	//	//IsPressed('A') to do letters on the keyboard
	//	position += nc::Vector2::left * speed * dt;
	//}
	//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT))
	//{
	//	position += nc::Vector2::right * speed * dt;
	//}

	/*for (nc::Vector2& point : points)
	{
		point = nc::Vector2{ nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	}*/

	direction = nc::Vector2::Rotate(direction, player.GetTransform().angle);
	player.GetTransform().position = player.GetTransform().position + direction;

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10,10,std::to_string(frametime).c_str());
	graphics.DrawString(10,20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());

	float v = (std::sin(t) + 1.0f) * 0.5f; // 0 - 2

	nc::Color c = nc::Lerp(nc::Color{ 0, 0, 1 }, nc::Color{ 1, 0, 0 }, v);
	graphics.SetColor(c);

	nc::Vector2 p = nc::Lerp(nc::Vector2{ 400,300 }, nc::Vector2{ 400,100 }, v);
	graphics.DrawString(p.x, p.y, "Last Starfighter");

	if (gameOver) graphics.DrawString(400, 300, "Game Over");
	
	shape.Draw(graphics, transform);

	player.Draw(graphics);
	enemy.Draw(graphics);
}

int main() 
{ 
	DWORD ticks = GetTickCount(); //how many ticks in a second
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();

	shape.Load("shape.txt");
	player.Load("shape.txt");
	enemy.Load("enemy.txt");

	char name[] = "New Super Shapey Bros WiiU & Knuckles Featuring Dante From The Devil May Cry Series"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown(); 
}

