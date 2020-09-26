#include "GameObject.h"
#include "Game.h"
#include "Sprites.h"
CGameObject::CGameObject() {
	x = y = 0;
	vx = 0.07f;
}
void CGameObject::Update(DWORD dt) {
	x += vx * dt;
	if ((vx > 0 && x > 290) || (vx < 0 && x < 0)) vx = -vx;
}
void CGameObject::Render() {
	LPANIMATION ani;
	if (vx > 0) ani = CAnimations::GetInstance()->Get(500);
	else ani = CAnimations::GetInstance()->Get(501);

	ani->Render(x, y);
}

CGameObject::~CGameObject() {
	if (texture != NULL) texture->Release();
}