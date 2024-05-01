#pragma once

#include "pch.hpp"

using namespace ab;

struct GameObject
{
public:
	i32 pos_x = 0;
	i32 pos_y = 0;
	i32 sprite_index_x = 0;
	i32 sprite_index_y = 0;
};

struct Ship : public GameObject
{
public:
	u32 speed = 5;

	Ship()
	{
		pos_x = 100;
		pos_y = 100;
	}

	void move(i32 dir_x, i32 dir_y)
	{
		pos_x += speed * dir_x;
		pos_y += speed * dir_y;
	}
};
