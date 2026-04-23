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
	sf::Clock clock;
	GameManager* game;
	DummyEntity* Ball;
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

	bool BallDead;
	bool die = false;
	bool CanSpawn_projectiles;
	bool CanResistor;
	bool CanSpeeder;
	bool firstkickResistor;
	bool spawnSpeeder;

	void TryBall(DummyEntity* pEntity, int x, int y);
	void TryProjectile(DummyEntity* pEntity, int x, int y);
	void TryResistor(Resistor* pEntity, int x, int y);
	void TrySpeeder(Speeder* pEntity, int x, int y);
	void DrawLines();
	int PickNumber(int number, int total);
	void CreateBall(int size);
	void SpawnProjectile(int speed);
	void SpawnResistors(int Speed);
	void SpawnSpeeders(int Speed);
};


