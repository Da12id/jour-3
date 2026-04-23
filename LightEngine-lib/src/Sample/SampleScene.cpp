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

	width = GetWindowWidth();
	height = GetWindowHeight();
	HorizontalLane = width / 7;
	VerticalLane  = height / 9;

	lifeBall = 3;
	BallDead = false;
	text.setFont(game->GetFont());
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);

	//texte du narrateur
	const sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.width, textRect.height / 2.0f);
	text.setPosition(980 / 2.0f, 150);

	//texte du compteur de money
	Money.setFont(game->GetFont());
	Money.setCharacterSize(50);
	Money.setFillColor(sf::Color::White);

	const sf::FloatRect MoneyyRect = Money.getLocalBounds();
	Money.setOrigin(textRect.width, textRect.height / 2.0f);
	Money.setPosition(0,0);

	//Indication pour le bouton
	Indication.setFont(game->GetFont());
	Indication.setCharacterSize(20);
	Indication.setFillColor(sf::Color::White);

	const sf::FloatRect IndicationRect = Indication.getLocalBounds();
	Indication.setOrigin(textRect.width, textRect.height / 2.0f);
	Indication.setPosition(width /2 + width / 8 , 20 );

	srand(time(nullptr));


	CreateBall(40);

	CanResistor = false;
	firstkickResistor = false;
	spawnSpeeder = false;
	CanSpeeder = false;
	respawnBall = false;
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
		for (Speeder* speeders : Speeders)
		{
			if (speeders != nullptr)
				TrySpeeder(speeders, event.mouseButton.x, event.mouseButton.y);
		}
		if(Button != nullptr)
			PressedButton(Button, event.mouseButton.x, event.mouseButton.y);
		if(Button2 != nullptr)
			PressedButton2(Button2, event.mouseButton.x, event.mouseButton.y);
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
	Debug::Get()->DrawText(Indication.getPosition().x, Indication.getPosition().y, Indication.getString(), sf::Color::White);

	//mouvement projectiles
	for(auto it = Projectiles.begin(); it!=Projectiles.end();)
	{
		DummyEntity* Ennemie = *it; //pour bouger les projectiles utiliser Ennemie
		if (Ennemie->GetPosition().y <= 0)
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().y >= height)
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().x <= 0 )
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		if (Ennemie->GetPosition().x >= width)
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
	
	//mouvement resistors
	for (auto it = Resistors.begin(); it != Resistors.end();)
	{
		Resistor* Ennemie = *it; 
		if (Ennemie->GetPosition().y <= 0)
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().y >= height)
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().x <= 0)
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		if (Ennemie->GetPosition().x >= width)
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		Ennemie->SetDirection(Ennemie->HorizontalSpeed, Ennemie->VerticalSpeed, Ennemie->speed);
		it++;
	}

	if (ResistorDestroy == 2 && CanSpeeder == false)
	{
		text.setString("C'est pas grave, Tu ne pourras jamais touchée ces cibles");
		for (int x = 0; x < 5; x++)
		{
			SpawnSpeeders(x);
		}
		CanSpeeder = true;
		CreateButton();
	}
	for (auto it = Speeders.begin(); it != Speeders.end();)
	{
		Speeder* Ennemie = *it;
		if (Ennemie->GetPosition().y <= 0)
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().y >= height)
		{
			Ennemie->VerticalSpeed = -Ennemie->VerticalSpeed;
		}
		if (Ennemie->GetPosition().x <= 0)
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		if (Ennemie->GetPosition().x >= width)
		{
			Ennemie->HorizontalSpeed = -Ennemie->HorizontalSpeed;
		}
		Ennemie->SetDirection(Ennemie->HorizontalSpeed, Ennemie->VerticalSpeed, Ennemie->speed);
		it++;
	}
	if (SpeederDestroy == 5 && respawnBall == false)
	{
		text.setString("Ça se fait pas\nMoi je voulais juste créer un jeux\net toi tu casse tout");
		CreateButton2();
		respawnBall = true;
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

	for (auto it = Projectiles.begin(); it != Projectiles.end(); ++it)
	{
		if (*it == pEntity)
		{
			Projectiles.erase(it);
			break;
		}
	}
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
		
		for (auto it = Resistors.begin(); it != Resistors.end(); ++it)
		{
			if (*it == pEntity)
			{
				Resistors.erase(it);
				break;
			}
		}
		
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

	std::cout << "You kick speeder" <<pEntity->life << std::endl;

	if (pEntity->life == 0)
	{
		pEntity->Destroy();

		for (auto it = Speeders.begin(); it != Speeders.end(); ++it)
		{
			if (*it == pEntity)
			{
				Speeders.erase(it);
				break;
			}
		}
		Gold++;
		SpeederDestroy++;
	}
}

void SampleScene::PressedButton(DummyEntity* pEntity, int x, int y)
{
	if(pEntity->IsInside(x, y) == false)
		return;

	Button->Destroy();
	Button = nullptr;
	Indication.setString(" ");

	for (Speeder* speeders : Speeders)
	{
		speeders->VerticalSpeed = speeders->VerticalSpeed/5;
	}
	text.setString("Quoi comment t'as fait ça!!!");
	Gold -= 7;
}

void SampleScene::PressedButton2(DummyEntity* pEntity, int x, int y)
{
	if (pEntity->IsInside(x, y) == false)
		return;

	Button2->Destroy();
	Button2 = nullptr;
	Indication.setString(" ");

	CreateBall(40);
	
	text.setString("Attend t'a vraiment fais ça?\npour moi!");
	Gold -= 1;
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

void SampleScene::CreateButton()
{
	Button = CreateEntity<DummyEntity>(40, sf::Color::Green);
	Button->SetPosition(width - Button->GetRadius(), 0 + Button->GetRadius());
	Indication.setString("7 pèces pour acheter ralentisseur");
}

void SampleScene::CreateButton2()
{
	Button2 = CreateEntity<DummyEntity>(40, sf::Color::Cyan);
	Button2->SetPosition(width - Button2->GetRadius(), 0 + Button2->GetRadius());
	Indication.setString("1 pièce pour construire une balle");
}