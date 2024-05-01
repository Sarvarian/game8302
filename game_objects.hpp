#pragma once

#include "pch.hpp"

using namespace ab;

struct GameObject
{
public:
	u32 pos_x = 0;
	u32 pos_y = 0;
	u32 sprite_index_x = 0;
	u32 sprite_index_y = 0;
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
};
