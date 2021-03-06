#pragma once
class Camera;
class SoundManager;
class LevelOutdoor
{
public:
	LevelOutdoor(Camera* camera);
	virtual ~LevelOutdoor( );

	// C++11 make the class non-copyable
	LevelOutdoor( const LevelOutdoor& ) = delete;
	LevelOutdoor& operator=( const LevelOutdoor& ) = delete;

	void Tick(double deltaTime);
	void Paint();
	//getters
	int GetWidth() { return LEVEL_WIDTH; }

	static const int LEVEL_WIDTH = 3200;
	static const int LEVEL_HEIGHT = 5760;
	static const int TILE_SIZE = 32;

private:
	void ReadFromFileStream();
	RECT2 Rect(int pos);
	void TilesToDraw();
	void PaintTiles();
	void CreateActors();

	//BG Methods
	void Background(int number, double deltaTime);
	void BackgroundPaint();
	void BackgroundLoop();

	//Tile Actors Methods
	void EighPartBlock(int i, int &count, int boxWidth, int boxHeight,
		DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13);
	void SinglePartMetalLedge(int i, int &count, int boxWidth, int boxHeight,
		DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13);
	void SinglePartMetalBlock(int i, int &count, int boxWidth, int boxHeight,
		DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13);
	void SinglePartFlowerBlock(int i, int &count, int boxWidth, int boxHeight,
		DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13);
	void DoublePartClockBlock(int i, int &count, int boxWidth, int boxHeight,
		DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13);
	void SandBlock(int i, int &count, int boxWidth, int boxHeight,
		DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13);

	int m_ScreenWidth;
	int m_ScreenHeight;
	Bitmap* m_BmpBkMoonPtr = nullptr;
	Bitmap* m_BmpMapOutdoorPtr = nullptr;
	Camera* m_CameraPtr = nullptr;;
	DOUBLE2 m_CamPos;

	int m_x = 0;
	int m_y = 0;
	int m_xOff = 0;
	int m_yOff = 0;

	//Actors
	PhysicsActor* m_ActFloorPtr = nullptr;

	std::vector<int> m_MapArr;
	std::vector<PhysicsActor*> m_LevelCollisionPtrArr;

	//Sound
	Sound* m_SndOutSideIntro = nullptr;
	Sound* m_SndOutsideLoop = nullptr;
	double m_IntroTimer = 0.0;

	//BG
	Bitmap* m_BmpBackgroundPtr = nullptr;
	Bitmap* m_BmpLevelOutdoor1Ptr = nullptr;
	Bitmap* m_BmpLevelOutdoor2Ptr = nullptr;
	Bitmap* m_BmpLevelOutdoor3Ptr = nullptr;
	Bitmap* m_BmpLevelOutdoor4Ptr = nullptr;

	DOUBLE2 m_Pos1;
	DOUBLE2 m_Pos2;
	DOUBLE2 m_Pos3;
	DOUBLE2 m_Pos4;

	DOUBLE2 m_Pos12;
	DOUBLE2 m_Pos22;
	DOUBLE2 m_Pos32;
	DOUBLE2 m_Pos42;

	int m_BitmapWidth = 0;
};

 
