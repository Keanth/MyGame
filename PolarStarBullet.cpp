#include "stdafx.h"
#include "PolarStarBullet.h"
#include "BitmapManager.h"

#define GAME_ENGINE (GameEngine::GetSingleton())

int PolarStarBullet::m_InstanceCounter = 0;
int PolarStarBullet::m_Exp = INITIAL_EXP;

PolarStarBullet::PolarStarBullet(DOUBLE2 pos, int direction)
{
	m_BmpArrowPtr = MyGame::m_BitmapManagerPtr->LoadBitmap(String("./Assets/Images/Bullet.png"));
	m_HeroPos = pos; 
	m_Direction = direction;

	m_BulletWidth = BULLET_WIDTH_POLARSTAR;
	m_BulletHeight = BULLET_HEIGHT_POLARSTAR;

	Projectile::Init();
}

PolarStarBullet::~PolarStarBullet()
{
}

void PolarStarBullet::Tick(double deltaTime)
{
	Projectile::Tick(deltaTime);
}

void PolarStarBullet::Paint()
{
	Projectile::Paint();
}

RECT PolarStarBullet::Rect()
{
	RECT r;

	r.top = m_BulletHeight * 0;
	r.left = m_BulletWidth * 0;
	r.bottom = 32 + r.top;
	r.right = 32 + r.left;

	return r;
}