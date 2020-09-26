#pragma once
#include <d3dx9.h>
class CGameObject
{
protected:
	float x;
	float y;

	float vx;
	LPDIRECT3DTEXTURE9 texture;
public:
	CGameObject();
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void Update(DWORD dt);
	void Render();
	~CGameObject();
};
typedef CGameObject *LPGAMEOBJECT;
