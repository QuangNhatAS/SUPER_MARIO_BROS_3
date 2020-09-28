#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED			0.1f
#define MARIO_JUMP_SPEED			1.0f
#define MARIO_GRAVITY				0.4f

#define MARIO_STATE_IDLE			100
#define MARIO_STATE_WALKING_RIGHT	200
#define MARIO_STATE_WALKING_LEFT	300
#define MARIO_STATE_JUMP			400

#define MARIO_ANI_IDLE_RIGHT		0
#define MARIO_ANI_IDLE_LEFT			1
#define MARIO_ANI_WALKING_RIGHT		2
#define MARIO_ANI_WALKING_LEFT		3

class CMario : public CGameObject {
public:
	void SetState(int state);

	void Update(DWORD dt);
	void Render();
};

