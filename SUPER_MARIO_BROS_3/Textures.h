#pragma once
#include <Windows.h>
#include <unordered_map>
#include <d3dx9.h>
#include "Game.h"
using namespace std;
class CTextures
{
	static CTextures * __instance;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;
public:
	void Add(int id, LPCWSTR texturePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);
	static CTextures *GetInstance();
};

