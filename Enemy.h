#pragma once
#include "ContactListener.h"

class Hero;
class LevelOutdoor;
class BitmapManager;
class Enemy : public ContactListener
{
public:
	Enemy(LevelOutdoor* level, Hero* hero, DOUBLE2 position);
	virtual ~Enemy();

	Enemy(const Enemy&) = delete;
	Enemy& operator=(const Enemy&) = delete;
	
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

	void Tick(double deltaTime);
	void Paint();
	void RemoveEnemy();
	void RemoveContactListener();
	//getters
	PhysicsActor* GetActor();
	int GetHealth();
	//setters
	void SetHealth(int health);

private:
	void Idle();
	void MoveLeft();
	void MoveRight();
	void MoveTowardHero(double deltaTime);
	void Attack(double deltaTime);
	void DealDamage();
	void ApplyImpulse(double deltaTime);
	void UpdateVariables(double deltaTime);
	void CreateWorldMatrix();
	RECT Rect();
	void Anim();
	void ResetCurrentFrame();
	void Init();

	static const int BASE_DAMAGE = 3;
	static const int CLIP_SIZE = 48;
	static const int WALK_FR = 2;
	static const int WALK_FR_PER_SEC = 6;
	static const int MOVE_RANGE = 600;
	static const int ATT_FR = 3;
	static const int ATT_FR_PER_SEC = 2;

	enum class ActionState
	{
		IDLE,
		WALK,
		ATTACK
	};
	ActionState m_ActionState = ActionState::IDLE;

	DOUBLE2 m_Vel = DOUBLE2(0.0, 0.0);
	double m_Mass = 0.0;
	DOUBLE2 m_DesiredVel;

	PhysicsActor* m_ActEnemyPtr = nullptr;
	LevelOutdoor* m_LevelPtr = nullptr;
	Hero* m_HeroPtr = nullptr;

	static const int FULL_HEALTH = 100;
	int m_Health = FULL_HEALTH;

	PhysicsActor* m_ActIsHitPtr = nullptr;
	bool m_IsHit = false;

	DOUBLE2 m_PosDif;
	bool m_MoveWorthy = true;
	bool m_AttackWorthy = false;
	double m_AttackTime = 0.0;
	double m_DamageTime = 0.0;
	bool m_BoolDealDamage = true;

	DOUBLE2 m_Direction = DOUBLE2(1,1);
	int m_CurrentFrame = 0;
	double m_AccuTime = 0.0;
	bool m_BoolCurentFrame = true;

	// Bitmap Bank
	BitmapManager* m_BitmapManager = nullptr;
	Bitmap* m_BmpNpc1Ptr = nullptr;
	DOUBLE2 m_Position;
};

