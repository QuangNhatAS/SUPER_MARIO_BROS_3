#include "Brick.h"

void CBrick::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CBrick::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BRICK_BBOX_WIDTH;
	bottom = y + BRICK_BBOX_HEIGHT;
}
