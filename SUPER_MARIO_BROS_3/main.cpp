#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Sprites.h"
#include "Mario.h"
#include "Goomba.h"
#include "Brick.h"
#include "debug.h"
#define WINDOW_CLASS_NAME L"SUPER MARIO BROS 3"
#define MAIN_WINDOW_TITLE L"MAIN SCENE"

#define MARIO_TEXTURE_PATH L"mario.png"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO	0
#define ID_TEX_MISC		1
#define ID_TEX_ENEMIES	2
//#define ID_TEX_BBOX	3

CGame*game;
CMario*mario;
CGoomba*goomba;

vector<LPGAMEOBJECT> objects;

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
	case DIK_Z:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_A:
		mario->SetState(MARIO_STATE_IDLE);
		mario->SetLevel(MARIO_LEVEL_BIG);
		mario->SetPosition(50.0f, 0.0f);
		mario->SetSpeed(0, 0);
		break;
	default:
		break;
	}
}
void CSampleKeyHandler::OnKeyUp(int KeyCode) {
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
}
void CSampleKeyHandler::KeyState(BYTE *states) {
	//disable when mario die
	if (mario->GetState() == MARIO_STATE_DIE) return;
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
	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(166, 185, 255));
	textures->Add(ID_TEX_ENEMIES, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	CSprites *sprites = CSprites::GetInstance();
	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);

	//big
	sprites->Add(1000, 216, 243, 230, 270, texMario); //idle right

	sprites->Add(1001, 255, 243, 271, 270, texMario); //walk
	sprites->Add(1002, 295, 244, 311, 270, texMario);
	
	sprites->Add(1010, 176, 243, 190, 270, texMario); //idle left
	sprites->Add(1011, 135, 243, 151, 270, texMario); //walk
	sprites->Add(1012, 95, 244, 111, 270, texMario);

	//small
	sprites->Add(2000, 217, 89, 229, 104, texMario); //idle right

	sprites->Add(2001, 256, 89, 271, 105, texMario); //walk
	sprites->Add(2002, 217, 89, 229, 104, texMario);

	sprites->Add(2010, 177, 89, 189, 104, texMario); //idle left
	sprites->Add(2011, 135, 89, 150, 105, texMario); //walk
	sprites->Add(2012, 177, 89, 189, 104, texMario);

	sprites->Add(10000, 15, 209, 31, 225, texMario); //mario die

	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(3000, 254, 188, 270, 204, texMisc);//brick

	LPDIRECT3DTEXTURE9 texEnemies = textures->Get(ID_TEX_ENEMIES);
	sprites->Add(4000, 5, 14, 21, 30, texEnemies);//goomba
	sprites->Add(4001, 25, 14, 41, 30, texEnemies);
	sprites->Add(4002, 45, 21, 61, 30, texEnemies);//die

	LPANIMATION ani;
	//idle big right
	ani = new CAnimation(100);
	ani->Add(1000);
	animations->Add(100, ani);
	//move big right
	ani = new CAnimation(100);
	ani->Add(1000);
	ani->Add(1001);
	ani->Add(1002);
	animations->Add(101, ani);
	//idle big left
	ani = new CAnimation(100);
	ani->Add(1010);
	animations->Add(200, ani);
	//move big left
	ani = new CAnimation(100);
	ani->Add(1010);
	ani->Add(1011);
	ani->Add(1012);
	animations->Add(201, ani);

	//idle small right
	ani = new CAnimation(100);
	ani->Add(2000);
	animations->Add(300, ani);
	//move small right
	ani = new CAnimation(100);
	//ani->Add(2000);
	ani->Add(2001);
	ani->Add(2002);
	animations->Add(301, ani);
	//idle small left
	ani = new CAnimation(100);
	ani->Add(2010);
	animations->Add(400, ani);
	//move small left
	ani = new CAnimation(100);
	//ani->Add(2010);
	ani->Add(2011);
	ani->Add(2012);
	animations->Add(401, ani);
	//mario die
	ani = new CAnimation(100);
	ani->Add(10000);
	animations->Add(500, ani);

	//brick
	ani = new CAnimation(100);
	ani->Add(3000);
	animations->Add(600, ani);
	//goomba
	ani = new CAnimation(100);
	ani->Add(4000);
	ani->Add(4001);
	animations->Add(700, ani);
	//goomba die
	ani = new CAnimation(100);
	ani->Add(4002);
	animations->Add(800, ani);

	mario = new CMario();
	mario->AddAnimation(100); //big idle right
	mario->AddAnimation(200); //big idle left
	mario->AddAnimation(300); //small idle right
	mario->AddAnimation(400); //small idle left

	mario->AddAnimation(101); //big walking right
	mario->AddAnimation(201); //big walking left
	mario->AddAnimation(301); //small walking right
	mario->AddAnimation(401); //small walking left

	mario->AddAnimation(500); //mario die

	mario->SetPosition(0.0f, 100.0f);
	objects.push_back(mario);

	for (int i = 0; i < 5; i++) {
		CBrick* brick = new CBrick();
		brick->AddAnimation(600);
		brick->SetPosition(100.0f + i * 60.0f, 74.0f);
		objects.push_back(brick);

		brick = new CBrick();
		brick->AddAnimation(600);
		brick->SetPosition(100.0f + i * 60.0f, 90.0f);
		objects.push_back(brick);

		brick = new CBrick();
		brick->AddAnimation(600);
		brick->SetPosition(84.0f + i * 60.0f, 90.0f);
		objects.push_back(brick);
	}
	for (int i = 0; i < 30; i++)
	{
		CBrick* brick = new CBrick();
		brick->AddAnimation(600);
		brick->SetPosition(0 + i * 16.0f, 150);
		objects.push_back(brick);
	}
	for (int i = 0; i < 4; i++)
	{
		goomba = new CGoomba();
		goomba->AddAnimation(700);
		goomba->AddAnimation(800);
		goomba->SetPosition(200 + i * 60, 135);
		goomba->SetState(GOOMBA_STATE_WALKING);
		objects.push_back(goomba);
	}

}

void Update(DWORD dt) {
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	//update camera to follow mario

	float cx, cy;
	mario->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	CGame::GetInstance()->SetCamPos(cx, 0.0f);
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
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();

		//mario->Render();

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

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	Run();

	return 0;
}