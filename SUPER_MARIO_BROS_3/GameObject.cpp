#include "GameObject.h"
#include "Game.h"
#include "Sprites.h"
vector<LPANIMATION> CGameObject::animations;
CGameObject::CGameObject() {
	x = y = 0;
	vx = 0.07f;
	nx = 1;
}
void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}
void CGameObject::Update(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}
void CGameObject::Render() {
	
}

CGameObject::~CGameObject() {
	
}