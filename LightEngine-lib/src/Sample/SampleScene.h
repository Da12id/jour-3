#pragma once
#include "Scene.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System.hpp>
#include "GameManager.h"
#include <vector>

class DummyEntity;

class SampleScene : public Scene
{
	sf::Text text;
	sf::Clock clock;
	GameManager* game;
	DummyEntity* Ball;
	DummyEntity* Projectile;
	std::vector<DummyEntity*>Projectiles;

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;

private:
	int score;
	int HorizontalLane;
	int VerticalLane;
	int width;
	int height;
	float TimeScore;
	int lifeBall;
	bool BallDead;
	bool die = false;
	bool CanSpawn_projectiles;
	int moveHorizontal;
	int moveVertical;
	void TryBall(DummyEntity* pEntity, int x, int y);
	void TrySetSelectedEntity(DummyEntity* pEntity, int x, int y);
	void DrawLines();
	int PickNumber(int number, int total);
	void CreateBall(int size);
	void SpawnProjectile(int x);
};


