#include "Textures.h"
#include "debug.h"
CTextures *CTextures::__instance = NULL;

void CTextures::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor) {
	//textures[id] = CGame::GetInstance()->LoadTexture(texturePath);
	D3DXIMAGE_INFO info;
	LPDIRECT3DTEXTURE9 texture;

	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = CGame::GetInstance()->GetDirect3DDevice();

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,						// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,			// Transparent color
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] CreateTextureFromFile failed. File: %s\n", filePath);
		return;
	}
	textures[id] = texture;
	DebugOut(L"[INFO] Texture loaded Ok: %s \n", filePath);
}
LPDIRECT3DTEXTURE9 CTextures::Get(unsigned int i) {
	return textures[i];
}
CTextures*CTextures::GetInstance() {
	if (__instance == NULL) __instance = new CTextures();
	return __instance;
}