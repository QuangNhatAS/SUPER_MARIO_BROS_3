#pragma once
#include <d3dx9.h>
#include <vector>
#include "Sprites.h"
class CGameObject
{
protected:
	float x;
	float y;

	float vx;
	float vy;

	int nx;
	int state;
	static vector<LPANIMATION> animations;
public:
	CGameObject();
	void SetPosition(float x, float y) { this->x = x; this->y = y; }

	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }

	static void AddAnimation(int aniId);

	virtual void Update(DWORD dt);
	virtual void Render();
	~CGameObject();
};
typedef CGameObject *LPGAMEOBJECT;
