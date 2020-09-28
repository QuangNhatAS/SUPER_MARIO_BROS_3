#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#define DIRECTINPUT_VERSION 0x0800
#define KEYBOARD_BUFFER_SIZE 1024
//abstract class to define keyboard event handlers

class CKeyEventHandler {
public:
	virtual void KeyState(BYTE *state) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};
typedef CKeyEventHandler * LPKEYEVENTHANDLER;

class CGame
{
	static CGame *__instance;
	HWND hWnd;

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;
	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;

	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 didv;

	BYTE keyStates[256];
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];

	LPKEYEVENTHANDLER keyHandler;
public:
	void InitKeyboard(LPKEYEVENTHANDLER keyHandler);
	void Init(HWND hWnd);
	//LPDIRECT3DTEXTURE9 LoadTexture(LPCWSTR texturePath);

	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return this->backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	static CGame * GetInstance();
	~CGame();
};

