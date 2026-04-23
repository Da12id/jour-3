#pragma once
#include "Scene.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include "GameManager.h"
#include <vector>

class DummyEntity;
class Resistor;

class SampleScene : public Scene
{
	sf::Text text;
	sf::Text Money;
	sf::Clock clock;
	GameManager* game;
	DummyEntity* Ball;
	DummyEntity* Projectile;
	Resistor* resistor;
	std::vector<DummyEntity*>Projectiles;
	std::vector<Resistor*>Resistors;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

private:
	float dt;
	int Gold;
	int HorizontalLane;
	int VerticalLane;
	int width;
	int height;
	float TimeScore;
	int lifeBall;
	bool BallDead;
	bool die = false;
	bool CanSpawn_projectiles;
	bool CanResistor;
	bool firstkickResistor;
	int moveHorizontal;
	int moveVertical;
	int ProjectilesDestroy;
	int spawnMore;
	void TryBall(DummyEntity* pEntity, int x, int y);
	void TryProjectile(DummyEntity* pEntity, int x, int y);
	void TryResistor(Resistor* pEntity, int x, int y);
	void DrawLines();
	int PickNumber(int number, int total);
	void CreateBall(int size);
	void SpawnProjectile(int speed);
	void spawnResistors(int Speed);
};


