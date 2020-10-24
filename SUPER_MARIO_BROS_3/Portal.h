#pragma once
#include "GameObject.h"
class CPortal : public CGameObject
{
	int scene_id;

	int width;
	int height;
public:
	CPortal(float l, float t, float r, float b, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	int GetSceneId() { return scene_id; }
};

