#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"
#include "Mario.h"
#include "debug.h"
#define WINDOW_CLASS_NAME L"SUPER MARIO BROS 3"
#define MAIN_WINDOW_TITLE L"MAIN SCENE"

#define MARIO_TEXTURE_PATH L"mario.png"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO 0

CGame*game;
CMario*mario;

class CSampleKeyHandler : public CKeyEventHandler {
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
CSampleKeyHandler * keyHandler;

void CSampleKeyHandler::OnKeyDown(int KeyCode) {
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	default:
		break;
	}
}
void CSampleKeyHandler::OnKeyUp(int KeyCode) {
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
}
void CSampleKeyHandler::KeyState(BYTE *states) {
	if (game->IsKeyDown(DIK_RIGHT)) mario->SetState(MARIO_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT)) mario->SetState(MARIO_STATE_WALKING_LEFT);
	else mario->SetState(MARIO_STATE_IDLE);
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

void LoadResource() {
	CTextures *textures = CTextures::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	textures->Add(ID_TEX_MARIO, L"textures\\mario.png", BACKGROUND_COLOR);

	CSprites *sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
	//move right
	sprites->Add(1000, 212, 443, 233, 471, texMario);
	sprites->Add(1001, 236, 443, 259, 471, texMario);
	sprites->Add(1002, 262, 443, 284, 471, texMario);
	sprites->Add(1003, 291, 443, 314, 471, texMario);
	//move left
	sprites->Add(1010, 173, 443, 194, 471, texMario);
	sprites->Add(1011, 147, 443, 170, 471, texMario);
	sprites->Add(1012, 122, 443, 144, 471, texMario);
	sprites->Add(1013, 92, 443, 115, 471, texMario);

	LPANIMATION ani;
	//idle right
	ani = new CAnimation(100);
	ani->Add(1000);
	animations->Add(500, ani);
	//move right
	ani = new CAnimation(100);
	ani->Add(1000);
	ani->Add(1001);
	ani->Add(1002);
	ani->Add(1003);
	animations->Add(501, ani);
	//idle left
	ani = new CAnimation(100);
	ani->Add(1010);
	animations->Add(600, ani);
	//move left
	ani = new CAnimation(100);
	ani->Add(1010);
	ani->Add(1011);
	ani->Add(1012);
	ani->Add(1013);
	animations->Add(601, ani);

	mario = new CMario();
	mario->AddAnimation(500);
	mario->AddAnimation(600);
	mario->AddAnimation(501);
	mario->AddAnimation(601);

	mario->SetPosition(0.0f, 100.0f);
}

void Update(DWORD dt) {
	mario->Update(dt);
}

void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 backBuffer = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	if (d3ddv->BeginScene())
	{
		// Clear screen (back buffer) with a color
		d3ddv->ColorFill(backBuffer, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		mario->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}



int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHandler();
	game->InitKeyboard(keyHandler);

	LoadResource();

	Run();
	

	return 0;
}