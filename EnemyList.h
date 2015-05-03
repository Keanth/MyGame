#pragma once
class GraveKeeper;
class BulletList;
class Hero;
class EnemyBase;
class EnemyList
{
public:
	EnemyList(Hero* hero);
	virtual ~EnemyList();

	EnemyList(const EnemyList&) = delete;
	EnemyList& operator=(const EnemyList&) = delete;

	bool Add(EnemyBase* enemyPtr);
	bool Remove(EnemyBase* enemyPtr);
	void RemoveAll();
	void Tick(double deltaTime);
	void Paint();
	bool IsHit(PhysicsActor* actOtherPtr);
	int GetSize();
	void HeDead();

	static int PickUpCount;

private:
	const static int NR_OF_ENEMIES = 1;
	std::vector<EnemyBase*> m_EnemyPtrArr;
	Hero* m_HeroPtr = nullptr;
};

