#pragma once

#include "math.hpp"

namespace ab
{
namespace actor
{

struct Direction
{
public:

	Direction(f32 x, f32 y) : value(x, y)
	{
		normalize_if_longer_then_one();
	}

	vec2f32 vec() const { return value; }

private:

	vec2f32 value;

	Direction();

	bool is_longer_then_one() const
	{
		return value.length_squared().is_greater_then(1.0f);
	}

	void normalize_if_longer_then_one() const
	{
		if (is_longer_then_one())
		{
			value.normalize_inplace();
		}
	}

};

struct SpriteIndex
{
public:
	SpriteIndex(u16 x, u16 y) : value(x, y) {}
private:
	vec2u16 value;
	SpriteIndex();
};

struct Position
{
public:
	Position(i32 x, i32 y) : value(x, y) {}
	Position(vec2i32 value) : value(value) {}
	vec2i32 vec() const { return value; }
private:
	vec2i32 value;
	Position();
};

struct PositionTail
{
public:
	PositionTail(f32 x, f32 y) : value(x, y) {}
	vec2f32 vec() const { return value; }
private:
	vec2f32 value;
	PositionTail();
};

struct Speed
{
public:
	Speed(i32 value) : value(value) {}
	i32 scalar() const { return value; }
private:
	i32 value;
	Speed();
};

struct Velocity
{
public:
	Velocity(Speed speed, Direction direction) : value(direction.vec().scale(speed.scalar().to_f32())) {}
	vec2f32 vec() { return value; }
private:
	vec2f32 value;
	Velocity();
};

struct PositionTemp
{
public:
	PositionTemp(Position position, PositionTail extra, Velocity vel)
	{
		value = vec2i32_to_vec2f32(position.vec()).add(extra.vec()).add(vel.vec());
	}

	PositionTail tail()
	{
		PositionTail res = PositionTail();
	}

	Position position()
	{
		Position res = Position(vec2f32_to_vec2i32(value.floor()));
	}

private:
	vec2f32 value;
	PositionTemp();
};

struct Ship
{
public:
	void move(Direction direction)
	{
		Velocity vel = Velocity(speed_, direction);
		PositionTemp pos = PositionTemp(position_, position_extra_, vel);
		position_extra_ = pos.tail();
		position_ = pos.position();
	}

private:
	Position position_ = { 100, 100 };
	PositionTail position_extra_ = { 0.0f, 0.0f };
	SpriteIndex sprite_index_ = { 0, 0 };
	Speed speed_ = 5;

};

} // namespace actor
} // namespace ab

