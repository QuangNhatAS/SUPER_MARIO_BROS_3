#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
using namespace std;
class CSprite
{
	int id;
	int left;
	int top;
	int right;
	int bottom;
	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);
	void Draw(float x, float y);
};
typedef CSprite*LPSPRITE;

//manage sprites

class CSprites {
	static CSprites * __instance;
	unordered_map<int, LPSPRITE> sprites;
public:
	void Add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 texture);
	LPSPRITE Get(int id);
	static CSprites * GetInstance();
};

class CAnimationFrame {
	LPSPRITE sprite;
	DWORD time;
public:
	CAnimationFrame(LPSPRITE sprite, DWORD time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
};
typedef CAnimationFrame*LPANIMATION_FRAME;
//manage frame

class CAnimation {
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
public:
	CAnimation(int defaultTime) { this->defaultTime = defaultTime; currentFrame = -1; lastFrameTime = -1; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);
};
typedef CAnimation*LPANIMATION;
//manage Animations
class CAnimations {
	static CAnimations*__instance;
	unordered_map <int, LPANIMATION> animations;
public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	static CAnimations*GetInstance();
};