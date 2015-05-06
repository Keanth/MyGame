#include "stdafx.h"
#include "DamageHero.h"
#include "Hero.h"

void DamageHero::DealDamage(int damage)
{
	Hero::m_health -= damage;
}