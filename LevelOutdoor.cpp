#include "stdafx.h"		
#include "LevelOutdoor.h"
#include "MyGame.h"
#include "Camera.h"
#include "SoundManager.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

LevelOutdoor::LevelOutdoor(Camera* camera)
: m_CameraPtr(camera)
{
	m_ScreenWidth = GAME_ENGINE->GetWidth();
	m_ScreenHeight = GAME_ENGINE->GetHeight();

	m_BmpBkMoonPtr = new Bitmap(String("./Assets/Images/bkMoon.png"));
	m_BmpMapOutdoorPtr = new Bitmap(String("./Assets/Images/PrtOside.png"));

	ReadFromFileStream();

	CreateActors();

	m_SndOutsideLoop = MyGame::m_SoundManagerPtr->LoadSound(String("./Assets/Sounds/oside_loop.mp3"));
	m_SndOutsideLoop->Play();
	m_SndOutsideLoop->Pause();
}

LevelOutdoor::~LevelOutdoor()
{
	delete m_BmpBkMoonPtr;
	delete m_BmpMapOutdoorPtr;
	m_MapArr.clear();
	for (size_t i = 0; i < m_LevelCollisionPtrArr.size(); i++)
	{
		delete m_LevelCollisionPtrArr[i];
	}
	m_LevelCollisionPtrArr.clear();
	delete m_ActFloorPtr;
}

void LevelOutdoor::Tick(double deltaTime)
{
	m_CameraPtr->Tick(deltaTime);
	m_CamPos = m_CameraPtr->GetCamPos();
	TilesToDraw();
}

void LevelOutdoor::Paint()
{
	GAME_ENGINE->SetBitmapInterpolationModeLinear();
	GAME_ENGINE->SetViewMatrix(MATRIX3X2::CreateIdentityMatrix());
	GAME_ENGINE->DrawBitmap(m_BmpBkMoonPtr);
	GAME_ENGINE->SetViewMatrix(m_CameraPtr->GetViewMatrix());
	PaintTiles();
}

void LevelOutdoor::PaintTiles()
{
	DOUBLE2 pos;
	DOUBLE2 location = m_CameraPtr->GetCamPos();
	int w = LEVEL_WIDTH / TILE_SIZE; // = 100 tiles
	int h = LEVEL_HEIGHT / TILE_SIZE; // = 180 tiles
	int x;
	int y;
	double camScale = m_CameraPtr->GetCamScale();

	for (size_t i = 0; i < m_MapArr.size(); i++)
	{
		x = (i % w);
		y = (i / w % h);
		
		if (camScale > 1.0) //Able to zoom in and out
		{
			x *= TILE_SIZE;
			y *= TILE_SIZE;
			pos = DOUBLE2(x, y);
			GAME_ENGINE->DrawBitmap(m_BmpMapOutdoorPtr, pos, Rect(m_MapArr[i] - 1));
		}
		else if ((x >= m_x) && (x <= m_xOff) && (y >= m_y) && (y <= m_yOff)) //Only render if within viewport dimensions 
		{
			x *= TILE_SIZE;
			y *= TILE_SIZE;
			pos = DOUBLE2(x, y);
			GAME_ENGINE->DrawBitmap(m_BmpMapOutdoorPtr, pos, Rect(m_MapArr[i] - 1));
		}
	}
}

void LevelOutdoor::ReadFromFileStream()
{
	int mapValue;

	std::ifstream ifileStream("./Assets/Files/Map_Outdoor.txt");
	if (ifileStream.fail() == true)
	{
		GAME_ENGINE->MessageBox(String("File: \'Map_Outdoor\' could not opened properly."));
		return;
	}
	//extract
	std::string extractedLine;
	while (ifileStream.eof() == false)
	{
		//extract until newline
		getline(ifileStream, extractedLine);
		mapValue = atoi(extractedLine.c_str());
		m_MapArr.push_back(mapValue);
	}
	ifileStream.close();
}

RECT2 LevelOutdoor::Rect(int pos)
{
	int rowSize = m_BmpMapOutdoorPtr->GetWidth() / TILE_SIZE;
	int collumnSize = m_BmpMapOutdoorPtr->GetHeight() / TILE_SIZE;
	RECT2 tile;

	tile.left = (pos % rowSize) * TILE_SIZE;
	tile.right = tile.left + TILE_SIZE;
	tile.top = (pos / rowSize) * TILE_SIZE;
	tile.bottom = tile.top + TILE_SIZE;

	return tile;
}

void LevelOutdoor::TilesToDraw()
{
	//Calculate which tiles can be drawn, based upon the viewport
	DOUBLE2 location = m_CameraPtr->GetCamPos();
	m_x = int((location.x - GAME_ENGINE->GetWidth() / 2) / TILE_SIZE);
	m_y = int((location.y - GAME_ENGINE->GetHeight() / 2) / TILE_SIZE);
	m_xOff = m_x + (m_ScreenWidth / TILE_SIZE);
	m_yOff = m_y + (m_ScreenHeight / TILE_SIZE);
}

void LevelOutdoor::CreateActors()
{
	TilesToDraw();
	int count = 0;
	DOUBLE2 pos;
	int w = LEVEL_WIDTH / TILE_SIZE; // = 100 tiles
	int h = LEVEL_HEIGHT / TILE_SIZE; // = 180 tiles
	PhysicsActor* localActor = nullptr;
	bool checkIs13 = false;
	int boxWidth = 0;
	int boxHeight = 2 * TILE_SIZE;

	for (size_t i = 0; i < m_MapArr.size(); i++)
	{
		int x = (i % w);
		int y = (i / w % h);
		x *= TILE_SIZE;
		y *= TILE_SIZE;

		EighPartBlock(i, count, boxWidth, boxHeight, pos, x, y, localActor, checkIs13);
		SinglePartMetalLedge(i, count, boxWidth, boxHeight, pos, x, y, localActor, checkIs13);
		SinglePartMetalBlock(i, count, boxWidth, boxHeight, pos, x, y, localActor, checkIs13);
		SinglePartFlowerBlock(i, count, boxWidth, boxHeight, pos, x, y, localActor, checkIs13);
		DoublePartClockBlock(i, count, boxWidth, boxHeight, pos, x, y, localActor, checkIs13);

	}
}

void LevelOutdoor::EighPartBlock(int i, int &count, int boxWidth, int boxHeight,
	DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13)
{
	if (m_MapArr[i] == 13) // number 13 to 29 --> 8 part block
	{
		if (m_MapArr[i + 4] == 13)
		{
			count++;
		}
		else
		{
			count++;

			boxWidth = (4 * TILE_SIZE) * count; // 4 * 32 * count
			boxHeight = 2 * TILE_SIZE;

			if (m_MapArr[i + 2] == 15)
			{
				pos = DOUBLE2(x - (boxWidth / 2) + TILE_SIZE * 4, y + boxHeight / 2);

			}
			else
			{
				pos = DOUBLE2(x - (boxWidth / 2) + TILE_SIZE * 2, y + boxHeight / 2);
			}

			localActor = new PhysicsActor(pos, 0, BodyType::STATIC);
			localActor->AddBoxShape(boxWidth, boxHeight, 0, 0);
			m_LevelCollisionPtrArr.push_back(localActor);

			count = 0;

			checkIs13 = false; //Exit
		}
	}
}

void LevelOutdoor::SinglePartMetalLedge(int i, int &count, int boxWidth, int boxHeight,
	DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13)
{
	if (m_MapArr[i] == 59) // number 59 --> Single part metal ledge
	{
		if (m_MapArr[i + 1] == 59)
		{
			count++;
		}
		else
		{
			count++;

			boxWidth = TILE_SIZE * count; // 32 * count
			boxHeight = TILE_SIZE;

			pos = DOUBLE2(x - (boxWidth / 2) + TILE_SIZE, y + (boxHeight / 2));

			localActor = new PhysicsActor(pos, 0, BodyType::STATIC);
			localActor->AddBoxShape(boxWidth, boxHeight, 0, 0);
			m_LevelCollisionPtrArr.push_back(localActor);

			count = 0;
		}
	}
}

void LevelOutdoor::SinglePartMetalBlock(int i, int &count, int boxWidth, int boxHeight,
	DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13)
{
	if (m_MapArr[i] == 47) // number 47 --> Single part metal block
	{
		if (m_MapArr[i + 1] == 47)
		{
			count++;
		}
		else
		{
			count++;

			boxWidth = TILE_SIZE * count; // 32 * count
			boxHeight = TILE_SIZE;

			pos = DOUBLE2(x - (boxWidth / 2) + TILE_SIZE, y + (boxHeight / 2));

			localActor = new PhysicsActor(pos, 0, BodyType::STATIC);
			localActor->AddBoxShape(boxWidth, boxHeight, 0, 0);
			m_LevelCollisionPtrArr.push_back(localActor);

			count = 0;
		}
	}
}

void LevelOutdoor::SinglePartFlowerBlock(int i, int &count, int boxWidth, int boxHeight,
	DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13)
{
	if (m_MapArr[i] == 49) // number 47 --> Single part flower block
	{
		if (m_MapArr[i + 1] == 49)
		{
			count++;
		}
		else
		{
			count++;

			boxWidth = TILE_SIZE * count; // 32 * count
			boxHeight = TILE_SIZE;

			pos = DOUBLE2(x - (boxWidth / 2) + TILE_SIZE, y + (boxHeight / 2));

			localActor = new PhysicsActor(pos, 0, BodyType::STATIC);
			localActor->AddBoxShape(boxWidth, boxHeight, 0, 0);
			m_LevelCollisionPtrArr.push_back(localActor);

			count = 0;
		}
	}
}

void LevelOutdoor::DoublePartClockBlock(int i, int &count, int boxWidth, int boxHeight,
	DOUBLE2 pos, int x, int y, PhysicsActor* localActor, bool checkIs13)
{
	if (m_MapArr[i] == 54) // number 54 --> Double part clock block
	{
		boxWidth = TILE_SIZE * 2; // 32 * 2
		boxHeight = TILE_SIZE;

		pos = DOUBLE2(x + TILE_SIZE, y + (boxHeight / 2));

		localActor = new PhysicsActor(pos, 0, BodyType::STATIC);
		localActor->AddBoxShape(boxWidth, boxHeight, 0, 0);
		m_LevelCollisionPtrArr.push_back(localActor);

		count = 0;
	}
}