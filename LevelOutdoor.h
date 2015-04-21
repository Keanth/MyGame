#pragma once
class Camera;
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

private:
	void ReadFromFileStream();
	RECT2 Rect(int pos);
	void TilesToDraw();
	void PaintTiles();
	void CreateActors();

	static const int TILE_SIZE = 32;

	int m_ScreenWidth;
	int m_ScreenHeight;
	Bitmap* m_BmpBkMoonPtr = nullptr;
	Bitmap* m_BmpMapOutdoorPtr = nullptr;
	Camera* m_CameraPtr = nullptr;;
	DOUBLE2 m_CamPos;

	std::vector<int> m_MapArr;

	int m_x = 0;
	int m_y = 0;
	int m_xOff = 0;
	int m_yOff = 0;

	//
	PhysicsActor* m_ActFloorPtr = nullptr;

	std::vector<PhysicsActor*> m_LevelCollisionPtrArr;

};

 
