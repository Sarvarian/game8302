#pragma once

#include "math.hpp"

namespace ab
{
namespace actor
{

struct Direction
{
public:
	Direction(f32 x, f32 y) : value(x, y) {}

	vec2f32 mul(f32 rhs)
	{
		return value.mul(rhs);
	}

	bool is_longer_then_one()
	{
		return value.length_squared().is_greater_then(1.0f);
	}

	void normalize_if_longer_then_one()
	{
		if (is_longer_then_one())
		{
			value.normalize_inplace();
		}
	}

private:
	vec2f32 value;
};

struct SpriteIndex
{
public:
	SpriteIndex() = default;
	SpriteIndex(u16 x, u16 y) : value(x, y) {}

private:
	vec2u16 value;
};

struct Position
{
public:
	Position() = default;
	Position(i32 x, i32 y) : value(x, y) {}

private:
	vec2i32 value;
};

struct PositionTail
{
public:
	PositionTail() = default;
	PositionTail(f32 x, f32 y) : value(x, y) {}

private:
	vec2f32 value;
};

struct Speed
{
public:
	Speed(i32 value) : value(value) {}

	i32 amount()
	{
		return value;
	}

	f32 to_float()
	{
		return value.to_float();
	}

private:
	i32 value;
};

struct Velocity
{
public:
	Velocity(Speed speed, Direction direction)
		: value(direction.mul(speed.to_float())) {}

private:
	vec2f32 value;

	Velocity() = default;
};

struct Ship
{
public:
	Ship()
	{
		position_ = ;
	}

	void move(vec2f32 direction)
	{
		direction.normalize_if_longer_then_one();

		fvec2 vel = dir.multiply(speed_.to_float());
		fvec2 pos = fvec2(position_);
		pos += vel;
		pos += position_extra_;

		//position_extra_;

			// position_ += speed_ * dir;
	}

private:
	Position position_ = { 100, 100 };
	PositionTail tail_ = { 0.0f, 0.0f };
	SpriteIndex sprite_index_ = { 0, 0 };
	Speed speed_ = 5;

};

} // namespace actor
} // namespace ab

