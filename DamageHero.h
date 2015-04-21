//STATIC

#pragma once
class DamageHero
{
public:
	DamageHero(const DamageHero&) = delete;
	DamageHero& operator=(const DamageHero&) = delete;

	static void DealDamage(int damage);
};

