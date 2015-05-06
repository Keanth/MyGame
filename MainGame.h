#pragma once
class LevelOutdoor;
class Hero;
class Camera;
class PolarStarBullet;
class BulletList;
class GraveKeeper;
class PickUpList;
class EnemyList;
class HUD;
class ButtonManager;
class PickUpBase;
class HealthUp;
class Doritos;
class NightSpirit;
class EnemyBase;

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

	//getters
	BulletList* GetBulletList() { return m_BulletListPtr; }

	static bool m_IsPaused;
	static PickUpList* m_PickUpListPtr;

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
	void PopulatePickUpList();
	void PopulateSound();

	Hero* m_HeroPtr = nullptr;
	LevelOutdoor* m_LevelOutdoorPtr = nullptr;
	Camera* m_CameraPtr = nullptr;
	BulletList* m_BulletListPtr = nullptr;
	HUD* m_HudPtr = nullptr;
	HealthUp* m_HealthUpPtr = nullptr;
	Doritos* m_DoritosPtr = nullptr;

	//Enemies
	EnemyList* m_EnemyListPtr = nullptr;
	std::vector<EnemyBase*> m_EnemyPtrArr;
	
	// ==== TESTING ====
	void InitTestButton();
	void DrawUnderlay();
	void CheckHit();
	void CheckTestMenu();

	bool m_BoolTestMenu = false;
	bool m_EnemySpawn = true;

	std::vector<ButtonManager*> m_ButtonManagerPtrArr;
};