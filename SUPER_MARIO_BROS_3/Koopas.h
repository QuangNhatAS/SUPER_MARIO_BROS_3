#pragma once
#include "GameObject.h"
class CKoopas : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

