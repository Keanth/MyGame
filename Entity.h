#pragma once
#include "ContactListener.h"
#include "BitmapManager.h"
#include "DamageHero.h"
#include "LevelOutdoor.h"
#include "PolarStarBullet.h"
#include "BitmapManager.h"

class Hero;
class LevelOutdoor;
class PolarStarBullet;
class Entity : public ContactListener
{
public:
	Entity();
	virtual ~Entity();

	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	virtual void BeginContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr) = 0;
	virtual void EndContact(PhysicsActor *actThisPtr, PhysicsActor *actOtherPtr) = 0;
	virtual void ContactImpulse(PhysicsActor *actThisPtr, double impulse) = 0;

	// Methods
	virtual void Tick(double deltaTime);
	virtual void Paint();
	virtual void RemoveContactListener();

	//Getters
	virtual PhysicsActor* GetActor() { return m_ActPtr; }
	virtual DOUBLE2 GetPosition() { return m_ActPtr->GetPosition(); }

protected:
	// Constants 
	const int TILE_SIZE = 32;
	// Methods
	virtual void Init();
	void UpdateVariables(double deltaTime);
	virtual void CreateWorldMatrix();
	virtual void Idle();
	virtual void MoveLeft();
	virtual void MoveRight();
	virtual void ApplyImpulse(double deltaTime);
	virtual RECT Rect() = 0;
	virtual void Anim() = 0;
	virtual void ResetCurrentFrame();

	// Enum classes
	enum class ActionState
	{
		WALK,
		IDLE,
		UP,
		STARTJUMP,
		STOPJUMP,
		BOOSTER,
		ATTACK,
		HIT,
		DEATH
	};
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	ActionState m_ActionState = ActionState::IDLE;
	Direction m_Direction = Direction::RIGHT;

	// Movement
	int m_BaseSpeed = 0;
	DOUBLE2 m_Vel = DOUBLE2(0.0, 0.0);
	double m_Mass = 0.0;
	DOUBLE2 m_DesiredVel;
	int m_CurrentFrame = 0;
	double m_AccuTime = 0.0;
//	DOUBLE2 m_Direction = DOUBLE2(1, 1);

	// Actors
	PhysicsActor* m_ActPtr = nullptr;

	// Bools
	bool m_BoolCurrentFrame = true;
	bool m_OnFloor = false;
};

