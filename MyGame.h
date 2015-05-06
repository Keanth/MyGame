//-----------------------------------------------------------------
// Game File
// C++ Source - DAEGameV1_2_31.h - version v2_16 jan 2015
// Copyright DAE Programming Team
// http://www.digitalartsandentertainment.be/
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Student data
// Name: Lenaerts Kenneth
// Group: 1DAE03
//-----------------------------------------------------------------

#pragma once
#include "Resource.h"	
#include "AbstractGame.h"

enum class GameState
{
	MAIN_MENU,
	MAIN_GAME,
	OPTIONS,
	PAUSE,
	EXIT
};

class MainMenu;
class MainGame;
class Pause;
class Exit;
class BitmapManager;
class SoundManager;
class IOManager;
class MyGame : public AbstractGame
{
public:
	MyGame();
	virtual ~MyGame();

	MyGame(const MyGame&) = delete;
	MyGame& operator=(const MyGame&) = delete;

	virtual void GameInitialize(GameSettings &gameSettings);
	virtual void GameStart();
	virtual void GameEnd();
	virtual void GameTick(double deltaTime);
	virtual void GamePaint(RECT rect);
	
	static void InitMainMenu();
	static void InitMainGame();
	static void InitPause();
	static void InitExit();

	static GameState m_GameState;
	bool m_CreateObj = true;

	static const int TILE_SIZE = 32;

	// Bank
	static BitmapManager* m_BitmapManagerPtr;
	static SoundManager* m_SoundManagerPtr;

private:
	void UpdateGameStates(double deltaTime);
	void DrawGameStates();

	static MainMenu* m_MainMenu;
	static MainGame* m_MainGame;
	static Pause* m_Pause;
	static Exit* m_Exit;

	// Bank
	void PopulateBank();

	//Log
	void WriteToLog(int number);
	IOManager* m_IOManagerPtr = nullptr;
};
