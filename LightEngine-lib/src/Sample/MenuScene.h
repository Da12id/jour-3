#pragma once
#include "Scene.h"
#include "GameManager.h"
#include "SampleScene.h"
#include "Debug.h"
#include <ctime>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
class MenuScene : public Scene
{
	sf::Text text;

	GameManager* game = GameManager::Get();

	MenuScene* m_menuscene;
	MenuScene* GetgmenuScene() { return m_menuscene; };
	void OnInitialize() override;
	virtual void OnEvent(const sf::Event& event) override;
	virtual void OnUpdate() override;
};

