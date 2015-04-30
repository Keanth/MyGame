#include "stdafx.h"
#include "Enemy.h"
#include "Entity.h"

#include "MyGame.h"
#include "PickUpList.h"
#include "EnemyList.h"
#include "MainGame.h"
#include "PickUpBase.h"
#include "Doritos.h"
#include "HealthUp.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

Enemy::Enemy(LevelOutdoor* level, Hero* hero, DOUBLE2 position)
{
	m_LevelPtr = level; 
	m_HeroPtr = hero; 
	m_Position = position;


	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Tick(double deltaTime)
{
	EnemyBase::Tick(deltaTime);
}

void Enemy::Paint()
{
	EnemyBase::Paint();
}