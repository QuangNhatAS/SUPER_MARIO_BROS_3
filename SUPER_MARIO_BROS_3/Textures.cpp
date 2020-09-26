#include "Textures.h"
CTextures *CTextures::__instance = NULL;

void CTextures::Add(int id, LPCWSTR texturePath, D3DCOLOR transparentColor) {
	textures[id] = CGame::GetInstance()->LoadTexture(texturePath);
}
LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i) {
	return textures[i];
}
CTextures*CTextures::GetInstance() {
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}