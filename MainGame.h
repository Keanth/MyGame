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
class EndGame;
class EnemyBase;
class DialogueTree;
class BitmapManager;
class CurlyBrace;

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
	static bool m_DialogueActive;

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
	void StopRunning(char key);
	void Pause(int number);
	void Inventory();
	void QuitGame(int number, double deltaTime);
	void Dialogue(int number, double deltaTime);
	void MovieBorder(int number, double deltaTime);

	Hero* m_HeroPtr = nullptr;
	CurlyBrace* m_CurlyBracePtr = nullptr;
	LevelOutdoor* m_LevelOutdoorPtr = nullptr;
	Camera* m_CameraPtr = nullptr;
	BulletList* m_BulletListPtr = nullptr;
	HUD* m_HudPtr = nullptr;
	HealthUp* m_HealthUpPtr = nullptr;
	Doritos* m_DoritosPtr = nullptr;
	EndGame* m_EndGamePtr = nullptr;
	DialogueTree* m_DialogueTreePtr = nullptr;
	BitmapManager* m_BitmapManagerPtr = nullptr;

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

	bool m_IsPauseActive = false;
	bool m_IsEndGameActive = false;
	bool m_DialogueWorthy = true;
	bool m_IsMovieBorderActive = true;
	double m_MovieBorderOffset = 100;
};