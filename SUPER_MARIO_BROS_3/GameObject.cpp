#include "GameObject.h"
#include "Game.h"
CGameObject::CGameObject(LPCWSTR filePath) {
	x = y = 0;
	texture = CGame::GetInstance()->LoadTexture(filePath);
}
void CGameObject::Update(DWORD dt) {

}
void CGameObject::Render() {
	CGame::GetInstance()->Draw(x, y, texture);
}
void CBrick::Update(DWORD dt) {
	x += 0.1f * dt;
	if (x > 320) x = 0;
}
CGameObject::~CGameObject() {
	if (texture != NULL) texture->Release();
}