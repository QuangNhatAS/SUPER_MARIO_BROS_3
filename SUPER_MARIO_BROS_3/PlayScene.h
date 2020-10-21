#pragma once
#include "Scene.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"

#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"
#include "Koopas.h"

class CPlayScene : public CScene
{
protected:
	CMario *player;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void UnLoad();
	virtual void Update(DWORD dt);
	virtual void Render();

	CMario * GetPlayer() { return player; }
};

class CPlaySceneKeyHandler : public CSceneKeyHandler {
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};

	CPlaySceneKeyHandler(CScene *s) : CSceneKeyHandler(s) {};
};

