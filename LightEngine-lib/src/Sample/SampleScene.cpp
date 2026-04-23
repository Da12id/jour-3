#include "SampleScene.h"
#include <iostream>
#include "DummyEntity.h"
#include "Resistor.h"
#include "Speeder.h"

#include "Debug.h"

void SampleScene::OnInitialize()
{
	clock.restart();
	dt = 0.0f;

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

	Money.setFont(game->GetFont());
	Money.setCharacterSize(50);
	Money.setFillColor(sf::Color::White);

	const sf::FloatRect MoneyyRect = Money.getLocalBounds();
	Money.setOrigin(textRect.width, textRect.height / 2.0f);
	Money.setPosition(0,0);

	srand(time(nullptr));

	width = GetWindowWidth();
	height = GetWindowHeight();
	HorizontalLane = width / 7;
	VerticalLane  = height / 9;

	CreateBall(40);

	CanResistor = false;
	firstkickResistor = false;
	spawnSpeeder = false;
	CanSpeeder = false;
}

void SampleScene::OnEvent(const sf::Event& event)
{

	if (event.type != sf::Event::EventType::MouseButtonPressed)
		return;

	if (event.mouseButton.button == sf::Mouse::Button::Left)
	{
		TryBall(Ball, event.mouseButton.x, event.mouseButton.y);
		for(DummyEntity* Projectile : Projectiles)
		{
			if (Projectile != nullptr)
				TryProjectile(Projectile, event.mouseButton.x, event.mouseButton.y);
		}
		for (Resistor* resistor : Resistors)
		{
			if (resistor != nullptr)
				TryResistor(resistor, event.mouseButton.x, event.mouseButton.y);
		}
	}
}


void SampleScene::OnUpdate()
{
	if(lifeBall == 3)
	{
		text.setString("Salut \nDésolé de te dire ça mais\nLe jeu n'est prêt");
	}
	else if(lifeBall == 2)
	{
		text.setString("Hey arrête tu vas la casser");
		Ball->Destroy();
		CreateBall(35);
	}
	else if(lifeBall ==1)
	{
		text.setString("T'as pas intéret a la casser");
		Ball->Destroy();
		CreateBall(30);
	}
	else if(CanSpawn_projectiles == false)
	{
		text.setString("Tu vas me le payer");
		Ball->Destroy();
		CanSpawn_projectiles = true;
		int x = 0;
		for(int x =0; x<5; x++)
		{
			SpawnProjectile(x);
		}
		Gold++;
	}

	//texte pour l'argent qu'on a
	Money.setString("vous avez " + std::to_string(Gold) + " pièces");

	Debug::Get()->DrawText(text.getPosition().x, text.getPosition().y, text.getString(), sf::Color::White);
	Debug::Get()->DrawText(Money.getPosition().x, Money.getPosition().y, Money.getString(), sf::Color::White);

	for(auto it = Projectiles.begin(); it!=Projectiles.end();)
	{
		DummyEntity* Ennemie = *it; //pour bouger les projectiles utiliser Ennemie
		if (Ennemie->GetPosition().y <= 0 + Ennemie->GetRadius())
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().y >= height - Ennemie->GetRadius())
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().x <= 0 + Ennemie->GetRadius())
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		if (Ennemie->GetPosition().x >= width - Ennemie->GetRadius())
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		Ennemie->SetDirection(Ennemie->HorizontalSpeed, Ennemie->VerticalSpeed, Ennemie->speed);
		it++;
	}
	if (ProjectilesDestroy == 5 && CanResistor == false)
	{
		text.setString("Quoi! Tu a détruit mes boules\nPrépare toi, c'est pas finie");
		for (int x = 0; x < 2; x++)
		{
			SpawnResistors(x);
		}
		CanResistor = true;

	}
	
	for (auto ça = Resistors.begin(); ça != Resistors.end();)
	{
		Resistor* Ennemie = *ça; 
		if (Ennemie->GetPosition().y <= 0 + Ennemie->GetRadius())
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().y >= height - Ennemie->GetRadius())
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().x <= 0 + Ennemie->GetRadius())
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		if (Ennemie->GetPosition().x >= width - Ennemie->GetRadius())
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		Ennemie->SetDirection(Ennemie->HorizontalSpeed, Ennemie->VerticalSpeed, Ennemie->speed);
		ça++;
	}

	if (ResistorDestroy == 2 && CanSpeeder == false)
	{
		text.setString("C'est pas grave, Tu ne pourras jamais touchée ces cibles");
		for (int x = 0; x < 5; x++)
		{
			SpawnSpeeders(x);
		}
		CanSpeeder = true;
	}
}

void SampleScene::TryBall(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	lifeBall--;
}

void SampleScene::TryProjectile(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntity->Destroy();
	ProjectilesDestroy++;
	Gold++;
}

void SampleScene::TryResistor(Resistor* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntity->life--;
	std::cout << pEntity->life << std::endl;

	if (firstkickResistor == false)
	{
		text.setString("HAHA celle là sont beaucoup plus résistante.");
		firstkickResistor = true;
	}

	if(pEntity->life == 0)
	{
		pEntity->Destroy();
		ResistorDestroy++;
		Gold++;
	}
}

void SampleScene::TrySpeeder(Speeder* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	pEntity->life--;
	std::cout << pEntity->life << std::endl;

	if (firstkickResistor == false)
	{
		text.setString("HAHA celle là sont beaucoup plus résistante.");
		firstkickResistor = true;
	}

	if (pEntity->life == 0)
	{
		pEntity->Destroy();
		Gold++;
	}
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

void SampleScene::SpawnProjectile(int Speed)
{
	Projectile = CreateEntity<DummyEntity>(40, sf::Color::Red);
	Projectiles.push_back(Projectile);
	Projectile->HorizontalSpeed = 10 + 5 * Speed;
	Projectile->VerticalSpeed = 50;
	Projectile->SetPosition(width/2, height/2);
}

void SampleScene::SpawnResistors(int Speed)
{
	resistor = CreateEntity<Resistor>(40, sf::Color::Yellow);
	Resistors.push_back(resistor);
	resistor->HorizontalSpeed = 10 + 7 * Speed;
	resistor->VerticalSpeed = 50;
	resistor->SetPosition(width / 2 + 5 *Speed, height / 2);
}

void SampleScene::SpawnSpeeders(int Speed)
{
	speeder = CreateEntity<Speeder>(30, sf::Color::White);
	Speeders.push_back(speeder);
	speeder->HorizontalSpeed = 10 + 7 * Speed;
	speeder->VerticalSpeed = 50;
	speeder->SetPosition(width / 2, height / 2);
}