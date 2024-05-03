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

private:
	vec2f32 value;
};

struct SpriteIndex
{
	u16 x, y;
};

struct Position
{
private:
	i32 x, y;
};

struct PositionExtra
{
private:
	float x, y;
};

struct Velocity
{
public:
	Velocity(i32 speed, vec2f32 direction)
	{
		x =
	}

private:
	vec2f32 = ;

	Velocity() = default;
};

struct Speed
{
public:
	Speed(i32 value) : value(value) {}

	f32 to_float()
	{
		return value.to_float();
	}

private:
	i32 value;
};

struct GameObject
{
public:
	Position position() const
	{
		return position_;
	}

	SpriteIndex sprite_index() const
	{
		return sprite_index_;
	}

protected:
	Position position_ = { 0, 0 };
	PositionExtra position_extra_ = { 0.0f, 0.0f };
	SpriteIndex sprite_index_ = { 0, 0 };
};

struct Ship : public GameObject
{
public:

	Ship()
	{
		position_.x = 100;
		position_.y = 100;
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
	Speed speed_ = 5;

};

} // namespace actor
} // namespace ab

