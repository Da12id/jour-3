#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	clock.restart();
	TimeScore = 0.0f;

	game = GameManager::Get();

	moveHorizontal = 50;
	moveVertical = 40;
	lifeBall = 3;
	BallDead = false;
	text.setFont(game->GetFont());
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);

	const sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width, textRect.height / 2.0f);
	text.setPosition(1000 / 2.0f, 150);

	srand(time(nullptr));

	width = GetWindowWidth();
	height = GetWindowHeight();
	HorizontalLane = width / 7;
	VerticalLane  = height / 9;

	CreateBall(40);
}

void SampleScene::OnEvent(const sf::Event& event)
{

	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		TryBall(Ball, event.mouseButton.x, event.mouseButton.y);
		for(int x =0; x<5; x++)
		{
			if (Projectiles[x] != nullptr)
				TrySetSelectedEntity(Projectiles[x], event.mouseButton.x, event.mouseButton.y);
		}
	}
}


void SampleScene::OnUpdate()
{
	if(lifeBall == 3)
	{
		text.setString("Salut \nDésolé de te dire ça mais\nRien n'est prêt");
	}
	else if(lifeBall == 2)
	{
		text.setString("Hey arrête tu vas la cassée");
		Ball->Destroy();
		CreateBall(35);
	}
	else if(lifeBall ==1)
	{
		text.setString("T'as pas intéret a la cassée");
		Ball->Destroy();
		CreateBall(30);
	}
	else if(CanSpawn_projectiles == false)
	{
		text.setString("Tu vas me le payer");
		Ball->Destroy();
		CanSpawn_projectiles = true;
		for(int x = 0; x<5; x++)
		{
			SpawnProjectile(x);
		}
	}
	Debug::Get()->DrawText(text.getPosition().x, text.getPosition().y, text.getString(), sf::Color::White);

	for(auto it = Projectiles.begin(); it!=Projectiles.end();)
	{
		DummyEntity* Ennemie = *it; //pour bouger les projectiles utiliser Ennemie
		it++;
	}
}

void SampleScene::TryBall(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	lifeBall--;
}

void SampleScene::TrySetSelectedEntity(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntity->Destroy();
}

void SampleScene::DrawLines()
{
	//Draw horizontal lines
	Debug::DrawLine(0, HorizontalLane, width, HorizontalLane, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 2, width, HorizontalLane * 2, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 3, width, HorizontalLane * 3, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 4, width, HorizontalLane * 4, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 5, width, HorizontalLane * 5, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 6, width, HorizontalLane * 6, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 7, width, HorizontalLane * 7, sf::Color::Red);
	Debug::DrawLine(0, HorizontalLane * 8, width, HorizontalLane * 8, sf::Color::Red);
	//Draw vertical lines
	Debug::DrawLine(VerticalLane, 0, VerticalLane, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 2, 0, VerticalLane * 2, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 3, 0, VerticalLane * 3, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 4, 0, VerticalLane * 4, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 5, 0, VerticalLane * 5, height, sf::Color::Green);
	Debug::DrawLine(VerticalLane * 6, 0, VerticalLane * 6, height, sf::Color::Green);
}

int SampleScene::PickNumber(int number, int total)
{
	number = rand() % (total - number + 1) + number;
	return number;
}

void SampleScene::CreateBall(int size)
{
	Ball = CreateEntity<DummyEntity>(size, sf::Color::Blue);
	Ball->SetPosition(width / 2, height / 2);
	Ball->SetRigidBody(true);
}

void SampleScene::SpawnProjectile(int x)
{
	Projectile = CreateEntity<DummyEntity>(30, sf::Color::Red);
	Projectiles.push_back(Projectile);
}
