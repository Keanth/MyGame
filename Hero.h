 #pragma once
#include "Entity.h"

class Hero : public Entity
{
public:
	Hero();
	virtual ~Hero();

	Hero(const Hero&) = delete;
	Hero& operator=(const Hero&) = delete;
	

	// Methods
	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr);
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse);
	virtual void Tick(double deltaTime);
	virtual void Paint();

	// Stats
	static int m_health;

protected:
	// Methods
	virtual void UserInput(double deltaTime);
	virtual void Up();
	virtual void Down();
	virtual void StartJump();
	virtual void StopJump();
	virtual void DownJump();
	virtual void StartBooster();
	virtual void StopBooster();
	virtual void BoosterTrail();
	virtual void GodMode();
	// Inheritance Methods
	virtual void Init();
	virtual void UpdateVariables(double deltaTime);
	virtual void Anim();
	virtual RECT Rect();
	virtual void Gone();
	
	// Class dependable constants
	static const int IDLE_FR = 1;
	static const int WALK_FR = 3;
	static const int WALK_FR_PER_SEC = 12;
	static const int JUMP_FR = 1;
	static const int JUMP_FR_PER_SEC = 1;
	static const int BOW_FR = 3;
	static const int BOW_FR_PER_SEC = 9;
	const int CLIP_SIZE = 32;
	const DOUBLE2 HERO_SPAWNPOINT = DOUBLE2(950, 5300);
	const double AIR_TIMER = 0.3;
	const double BOOSTER_TIMER = 0.6;
	const int BOOSTER_FR = 7;
	const int BOOSTER_FR_PER_SEC = 15;
	// Stats
	static const int INITIAL_HEALTH = 20;

	// Jump
	double m_Jump_Time = 0.0;
	bool m_ActiveJump = false;

	// Booster
	bool m_BoosterActive = false;
	double m_BoosterTimer = 0.0;
	Bitmap* m_BmpBoosterTrailPtr = nullptr;
	bool m_BoolBoosterTrail = false;
	int m_BoosterFrame = 0;
	
	// Bitmap Bank
	Bitmap* m_BmpHeroPtr = nullptr;

	//Shoot
	bool m_IsShootWorthy = true;

	bool m_Godmode = false;
};
