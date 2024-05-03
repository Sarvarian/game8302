#pragma once

// namespace ab
// {
// namespace primitives
// {

// typedef Sint8      i8;
// typedef Sint16     i16;
// typedef Sint32     i32;
// typedef Sint64     i64;
// typedef Uint8      u8;
// typedef Uint16     u16;
// typedef Uint32     u32;
// typedef Uint64     u64;

// typedef intptr_t   isize;
// typedef uintptr_t  usize;

// } // namespace primitives
// using namespace primitives;
// } // namespace ab

namespace ab
{
namespace math
{

struct f32
{
public:
	f32(float value) : value(value) {}

	f32 add(f32 rhs)
	{
		return f32(value + rhs.value);
	}

	void add_inplace(f32 rhs)
	{
		value = value + rhs.value;
	}

	f32 sub(f32 rhs)
	{
		return f32(value - rhs.value);
	}

	void sub_inplace(f32 rhs)
	{
		value = value - rhs.value;
	}

	f32 mul(f32 rhs)
	{
		return f32(value * rhs.value);
	}

	void mul_inplace(f32 rhs)
	{
		value = value * rhs.value;
	}

	f32 div(f32 rhs)
	{
		return f32(value / rhs.value);
	}

	void div_inplace(f32 rhs)
	{
		value = value / rhs.value;
	}

	bool is_greater_then(f32 rhs)
	{
		return value > rhs.value;
	}

private:
	friend class Convertor;
	float value = 0;
};

struct i32
{
public:
	i32(Sint32 value) : value(value) {}

	f32 to_float();

private:
	friend class Convertor;
	Sint32 value = 0;
};

struct u16
{
public:
	u16(Uint16 value) : value(value) {}

private:
	friend class Convertor;
	Uint16 value = 0;

};

namespace
{

template<typename T>
T vec2_length_squared(T x, T y)
{
	// --- (x * x) + (y * y) ---
	x = x.mul(x);
	y = y.mul(y);
	return x.add(y);
}

template<typename T>
T vec2_length(T x, T y)
{
	return std::sqrt(vec2_length_squared(x, y));
}

} // namespace

struct vec2f32
{
public:
	vec2f32(f32 x, f32 y) : x(x), y(y) {}

	vec2f32 add(vec2f32 rhs)
	{
		return vec2f32(x.add(rhs.x), y.add(rhs.y));
	}

	void add_inplace(vec2f32 rhs)
	{
		x.add_inplace(rhs.x);
		y.add_inplace(rhs.y);
	}

	vec2f32 sub(vec2f32 rhs)
	{
		return vec2f32(x.sub(rhs.x), y.sub(rhs.y));
	}

	void sub_inplace(vec2f32 rhs)
	{
		x.sub_inplace(rhs.x);
		y.sub_inplace(rhs.y);
	}

	f32 length_squared()
	{
		return vec2_length_squared(x, y);
	}

	f32 length()
	{
		return vec2_length(x, y);
	}

	vec2f32 normalize()
	{
		f32 len = length();
		f32 x = x.div(len);
		f32 y = y.div(len);
		return vec2f32(x, y);
	}

	vec2f32 normalize_inplace()
	{
		f32 len = length();
		x.div_inplace(len);
		y.div_inplace(len);
	}

	bool is_longer_then_one()
	{
		return length_squared().is_greater_then(1.0f);
	}

	void normalize_if_longer_then_one()
	{
		if (is_longer_then_one())
		{
			normalize_inplace();
		}
	}

private:
	f32 x, y;

};

class Convertor
{
private:
	friend class i32;
	friend class f32;

	static f32 i32tof32(const i32& i)
	{
		return f32((float)(i.value));
	}

};

f32 i32::to_float()
{
	return Convertor::i32tof32(*this);
}

} // namespace math

using math::f32;
using math::i32;
using math::u16;
using math::vec2f32;

} // namespace ab


