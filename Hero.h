#pragma once
#include "ContactListener.h"
class LevelOutdoor;
class PolarStarBullet;
class BitmapManager;
class Hero : public ContactListener
{
public:
	Hero();
	virtual ~Hero();

	Hero(const Hero&) = delete;
	Hero& operator=(const Hero&) = delete;

	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr); 
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);   
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);

	void Paint();
	void Tick(double deltaTime);

	//getters
	DOUBLE2 GetPosition() { return m_ActHeroPtr->GetPosition(); }
	PhysicsActor* GetActor() { return m_ActHeroPtr; }
	int GetDirection();

	// Stats
	static int m_health;

private:
	void UserInput(double deltaTime);
	RECT Rect();
	void Idle();
	void MoveRight();
	void MoveLeft();
	void Up();
	void CreateWorldMatrix();
	void Anim();
	void StartJump();
	void StopJump();
	void Booster();
	void UpdateVariables(double deltaTime);
	DOUBLE2 ApplyPivot();
	void ApplyImpulse(double deltaTime);

	PhysicsActor* m_ActHeroPtr = nullptr;
	PhysicsActor* m_ActHeroFeetPtr = nullptr;

	enum class ActionState
	{
		WALK,
		IDLE,
		UP,
		STARTJUMP,
		STOPJUMP,
		HIT,
		DEATH,
	}; 
	ActionState m_ActionState = ActionState::IDLE;

	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	Direction m_Direction = Direction::RIGHT;

	static const int IDLE_FR = 1;
	static const int WALK_FR = 3;
	static const int WALK_FR_PER_SEC = 12;
	static const int JUMP_FR = 1;
	static const int JUMP_FR_PER_SEC = 1;
	static const int BOW_FR = 3;
	static const int BOW_FR_PER_SEC = 9;
	const int CLIP_SIZE = 32;
	const DOUBLE2 HERO_SPAWNPOINT = DOUBLE2(200, 5300);
	static const double AIR_TIMER;

	DOUBLE2 m_HeroDirection = DOUBLE2(1,1);

	double m_AccuTime = 0;
	int m_CurrentFrame = 0;
	DOUBLE2 m_Vel = DOUBLE2(0.0, 0.0);
	double m_Mass = 0.0;
	DOUBLE2 m_DesiredVel;
	
	// Jump
	double m_Jump_Time = 0.0;
	bool m_Active = false;
	bool m_ActiveJump = false;
	bool m_OnFloor = false;

	// Booster
	bool m_BoostActive = false;
	int m_BoosterFuel = 50;

	// Stats
	static const int INITIAL_HEALTH = 20;

	// Bitmap Bank
	BitmapManager* m_BitmapManager = nullptr;
	Bitmap* m_BmpHeroPtr = nullptr;	
};