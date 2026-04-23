#include <SFML/Graphics.hpp>
#include <iostream>
#include"GameManager.h"
#include "MenuScene.h"
#include "SampleScene.h"
#include <cstdlib>
#include <crtdbg.h>
int main()
{
	GameManager* game = GameManager::Get();


	game->CreateWindow(1280, 720, "Game day 2", 60, sf::Color(50, 0, 50));
	game->LaunchScene< SampleScene>();
}