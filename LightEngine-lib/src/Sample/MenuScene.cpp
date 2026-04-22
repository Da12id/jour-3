#include "MenuScene.h"

void MenuScene::OnInitialize()
{
	GameManager* game = GameManager::Get();
	text.setFont(game->GetFont());
	text.setString("Press enter to start");
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);

	const sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin( textRect.width,  textRect.height / 2.0f);
	text.setPosition(1000 / 2.0f, 720 / 2.0f);
}

void MenuScene::OnEvent(const sf::Event& event)
{
	if (event.key.code == sf::Keyboard::Enter)
		game->LaunchScene< SampleScene>();
}

void MenuScene::OnUpdate()
{
	Debug::Get()->DrawText(text.getPosition().x, text.getPosition().y, text.getString(), sf::Color::White);
}
