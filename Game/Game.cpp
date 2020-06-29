// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "core.h"

bool Update(float dt)
{
	return false;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256)); 
	graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
}

int main() 
{ 
	char name[] = "New Super Random Lines Bros WiiU & Knuckles Featuring Dante From The Devil May Cry Series"; 
	Core::Init(name, 800, 600); 
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop(); 
	Core::Shutdown(); 
}

