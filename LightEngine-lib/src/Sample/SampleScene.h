#pragma once
#include "Scene.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include "GameManager.h"
#include <vector>

class DummyEntity;
class Resistor;
class Speeder;

class SampleScene : public Scene
{
	sf::Text text;
	sf::Text Money;
	sf::Text Indication;
	sf::Clock clock;
	GameManager* game;
	DummyEntity* Ball;
	DummyEntity* Button;
	DummyEntity* Button2;
	DummyEntity* Projectile;
	Resistor* resistor;
	Speeder* speeder;
	std::vector<DummyEntity*>Projectiles;
	std::vector<Resistor*>Resistors;
	std::vector<Speeder*>Speeders;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

private:
	float dt;
	float TimeScore;
	
	int Gold;
	int HorizontalLane;
	int VerticalLane;
	int width;
	int height;
	int lifeBall;
	int moveHorizontal;
	int moveVertical;
	int ProjectilesDestroy;
	int spawnMore;
	int ResistorDestroy;
	int SpeederDestroy;

	bool BallDead;
	bool die = false;
	bool CanSpawn_projectiles;
	bool CanResistor;
	bool CanSpeeder;
	bool firstkickResistor;
	bool spawnSpeeder;
	bool bottonPressed2;
	bool respawnBall;

	void TryBall(DummyEntity* pEntity, int x, int y);
	void TryProjectile(DummyEntity* pEntity, int x, int y);
	void TryResistor(Resistor* pEntity, int x, int y);
	void TrySpeeder(Speeder* pEntity, int x, int y);
	void PressedButton(DummyEntity* pEntity, int x, int y);
	void PressedButton2(DummyEntity* pEntity, int x, int y);
	void CreateBall(int size);
	void SpawnProjectile(int speed);
	void SpawnResistors(int Speed);
	void SpawnSpeeders(int Speed);
	void CreateButton();
	void CreateButton2();
};


