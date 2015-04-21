#pragma once
class LevelOutdoor;
class Hero;
class Camera;
class PolarStarBullet;
class BulletList;
class Enemy;
class EnemyList;
class HUD;
class ButtonManager;
class PickUpBase;
class HealthUp;
class Doritos;

class MainGame
{
public:
	MainGame();
	virtual ~MainGame();

	MainGame(const MainGame&) = delete;
	MainGame& operator=(const MainGame&) = delete;

	static DOUBLE2 m_HeroPos;

	void Tick(double deltaTime);
	void Paint();

	static bool m_IsPaused;

private:
	void InitObj();
	void RemoveAll();
	void PhysicsRendering();
	void CameraLock(double deltaTime);
	void EnemyHandler();
	void UpdateHero();
	void _Test();
	bool m_Physics = false;
	bool m_CameraLock = true;
	bool m_Shooting = false;


	Hero* m_HeroPtr = nullptr;
	LevelOutdoor* m_LevelOutdoorPtr = nullptr;
	Camera* m_CameraPtr = nullptr;
	BulletList* m_ArrowListPtr = nullptr;
	HUD* m_HudPtr = nullptr;
	HealthUp* m_HealthUpPtr = nullptr;
	Doritos* m_DoritosPtr = nullptr;

	EnemyList* m_EnemyListPtr = nullptr;
	std::vector<Enemy*> m_EnemyPtrArr;
	
	// ==== TESTING ====
	void InitTestButton();
	void DrawUnderlay();
	void CheckHit();
	void CheckTestMenu();

	bool m_BoolTestMenu = false;

	std::vector<ButtonManager*> m_ButtonManagerPtrArr;
};