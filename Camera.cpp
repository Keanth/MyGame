#include "stdafx.h"
#include "Camera.h"
#include "hero.h"
#include "LevelOutdoor.h"
#define GAME_ENGINE (GameEngine::GetSingleton())

Camera::Camera(Hero* avatarPtr)
:m_HeroPtr(avatarPtr)
{
	m_CameraDimension = DOUBLE2(GAME_ENGINE->GetWidth(), GAME_ENGINE->GetHeight());
}

Camera::~Camera()
{
}

MATRIX3X2 Camera::GetPlayerMatrix()
{
	double distance;
	double ratio;

	if (m_CamPos.x - m_HeroPtr->GetPosition().x < MAXRIGHT)
	{
		distance = (m_CamPos.x - m_HeroPtr->GetPosition().x);
		ratio = distance / MAXRIGHT;
		ratio *= ratio;
		if (ratio > 1)
		{
			m_CamPos.x = m_HeroPtr->GetPosition().x + ratio + distance;
		}
	}
	else if (-(m_CamPos.x - m_HeroPtr->GetPosition().x) < MAXLEFT)
	{
		distance = -(m_CamPos.x - m_HeroPtr->GetPosition().x);
		ratio = distance / MAXLEFT;
		ratio *= ratio;
		if (ratio > 1)
		{
			m_CamPos.x = m_HeroPtr->GetPosition().x - ratio - distance;
		}
	}

	if (m_CamPos.y - m_HeroPtr->GetPosition().y < MAXRIGHT)
	{
		distance = (m_CamPos.y - m_HeroPtr->GetPosition().y);
		ratio = distance / MAXRIGHT;
		ratio *= ratio;
		if (ratio > 1)
		{
			m_CamPos.y = m_HeroPtr->GetPosition().y + ratio + distance;
		}
	}
	else if (-(m_CamPos.y - m_HeroPtr->GetPosition().y) < MAXLEFT)
	{
		distance = -(m_CamPos.y - m_HeroPtr->GetPosition().y);
		ratio = distance / MAXLEFT;
		ratio *= ratio;
		if (ratio > 1)
		{
			m_CamPos.y = m_HeroPtr->GetPosition().y - ratio - distance;
		}
	}

	//Camera Borders
	if (m_CamPos.x - ((m_CameraDimension.x * m_CameraScale) / 2) < 0.0)
		m_CamPos.x = (m_CameraDimension.x * m_CameraScale) / 2;

	if (m_CamPos.x + ((m_CameraDimension.x * m_CameraScale) / 2) > LevelOutdoor::LEVEL_WIDTH)
		m_CamPos.x = LevelOutdoor::LEVEL_WIDTH - ((m_CameraDimension.x * m_CameraScale) / 2);

	if (m_CamPos.y + ((m_CameraDimension.y * m_CameraScale) / 2) >  LevelOutdoor::LEVEL_HEIGHT)
		m_CamPos.y = LevelOutdoor::LEVEL_HEIGHT - ((m_CameraDimension.y * m_CameraScale) / 2);

	if (m_CamPos.y - ((m_CameraDimension.y * m_CameraScale) / 2) < 0.0)
		m_CamPos.y = ((m_CameraDimension.y * m_CameraScale) / 2);

	MATRIX3X2 matPivot, matTranslate, matTransform, matScale;
	matPivot.SetAsTranslate(-(GAME_ENGINE->GetWidth() / 2), -(GAME_ENGINE->GetHeight() / 2));
	matScale.SetAsScale(m_CameraScale);
	matTranslate.SetAsTranslate(m_CamPos);

	matTransform = matPivot* matScale * matTranslate;
	return matTransform.Inverse();
}

MATRIX3X2 Camera::GetViewMatrix()
{
	//Camera Borders
	if (m_CamPos.x - ((m_CameraDimension.x * m_CameraScale) / 2) < 0.0)
		m_CamPos.x = (m_CameraDimension.x * m_CameraScale) / 2;

	if (m_CamPos.x + ((m_CameraDimension.x * m_CameraScale) / 2) >  LevelOutdoor::LEVEL_WIDTH)
		m_CamPos.x = LevelOutdoor::LEVEL_WIDTH - ((m_CameraDimension.x * m_CameraScale) / 2);

	if (m_CamPos.y + ((m_CameraDimension.y * m_CameraScale) / 2) > LevelOutdoor::LEVEL_HEIGHT)
		m_CamPos.y = LevelOutdoor::LEVEL_HEIGHT - ((m_CameraDimension.y * m_CameraScale) / 2);

	if (m_CamPos.y - ((m_CameraDimension.y * m_CameraScale) / 2) < 0.0)
		m_CamPos.y = ((m_CameraDimension.y * m_CameraScale) / 2);

	MATRIX3X2 matPivot, matTranslate, matTransform, matScale;
	matPivot.SetAsTranslate(-(GAME_ENGINE->GetWidth() / 2), -(GAME_ENGINE->GetHeight() / 2));
	matScale.SetAsScale(m_CameraScale);
	matTranslate.SetAsTranslate(m_CamPos);

	matTransform = matPivot* matScale * matTranslate;
	return matTransform.Inverse();
}

void Camera::Tick(double deltaTime)
{
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_UP))
	{
		m_CamPos.y -= CAM_MOVEMENT;
	}
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_DOWN))
	{
		m_CamPos.y += CAM_MOVEMENT;
	}
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_LEFT))
	{
		m_CamPos.x -= CAM_MOVEMENT;
	}
	if (GAME_ENGINE->IsKeyboardKeyDown(VK_RIGHT))
	{
		m_CamPos.x += CAM_MOVEMENT;
	}
	if (GAME_ENGINE->IsKeyboardKeyDown('T'))
	{
		m_CameraScale -= 0.01;
	}
	if (GAME_ENGINE->IsKeyboardKeyDown('Y'))
	{
		m_CameraScale += 0.01;
	}
}

DOUBLE2 Camera::GetCamPos()
{
	return DOUBLE2(m_CamPos.x, m_CamPos.y);
}

double Camera::GetCamScale()
{
	return m_CameraScale;
}