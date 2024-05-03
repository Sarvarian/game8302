#pragma once

namespace ab
{
namespace math
{
namespace primitives
{
typedef float      raw_f32;
typedef double     raw_f64;

typedef Sint8      raw_i8;
typedef Sint16     raw_i16;
typedef Sint32     raw_i32;
typedef Sint64     raw_i64;

typedef Uint8      raw_u8;
typedef Uint16     raw_u16;
typedef Uint32     raw_u32;
typedef Uint64     raw_u64;

typedef intptr_t   raw_isize;
typedef uintptr_t  raw_usize;
} // namespace primitives


/// @brief 
/// @tparam T FinalType
/// @tparam R RawType
template<typename T, typename R>
struct TNumber
{
public:
	typedef TNumber<T, R> Base; // Base Type (TNumber Type)
	typedef T             Type; // Final Type
	typedef R              Raw; // Raw Type

	TNumber(Raw v) : value(v) {}
	TNumber(Type v) : value(v.value) {}
	TNumber() : value(0) {}

	Type add(Type rhs)
	{
		return Type(value + rhs.value);
	}

	void add_inplace(Type rhs)
	{
		value = value + rhs.value;
	}

	Type sub(Type rhs)
	{
		return Type(value - rhs.value);
	}

	void sub_inplace(Type rhs)
	{
		value = value - rhs.value;
	}

	Type mul(Type rhs)
	{
		return Type(value * rhs.value);
	}

	void mul_inplace(Type rhs)
	{
		value = value * rhs.value;
	}

	Type div(Type rhs)
	{
		return Type(value / rhs.value);
	}

	void div_inplace(Type rhs)
	{
		value = value / rhs.value;
	}

	bool is_greater_then(Type rhs)
	{
		return value > rhs.value;
	}

protected:
	Raw get_raw()
	{
		return value;
	}

private:
	friend class Convertor;
	Raw value;

};

struct f32 : public TNumber<f32, primitives::raw_f32>
{
public:
	f32(Raw value) : Base(value) {}

	f32 sqrt()
	{
		return sqrtf(get_raw());
	}

private:

};

struct i32 : public TNumber<i32, primitives::raw_i32>
{
public:
	i32(Raw value) : Base(value) {}

	f32 to_float();

private:

};

struct u16 : public TNumber<u16, primitives::raw_u16>
{
public:
	u16(Raw value) : Base(value) {}

private:

};

struct u32 : public TNumber<u32, primitives::raw_u32>
{
public:
	u32(Raw value) : Base(value) {}

private:

};

struct u64 : public TNumber<u64, primitives::raw_u64>
{
public:
	u64(Raw value) : Base(value) {}

private:

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
	return vec2_length_squared(x, y).sqrt();
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

	vec2f32 mul(f32 rhs)
	{
		return vec2f32(x.mul(rhs), y.mul(rhs));
	}

	void mul_inplace(f32 rhs)
	{
		x.mul_inplace(rhs);
		y.mul_inplace(rhs);
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
		return vec2f32(x.div(len), y.div(len));
	}

	void normalize_inplace()
	{
		f32 len = length();
		x.div_inplace(len);
		y.div_inplace(len);
	}

private:
	friend class Convertor;
	f32 x;
	f32 y;

};

struct vec2i32
{
public:
	vec2i32(i32 x, i32 y) : x(x), y(y) {}

private:
	friend class Convertor;
	i32 x;
	i32 y;
};

struct vec2u16
{
public:
	vec2u16(u16 x, u16 y) : x(x), y(y) {}

private:
	friend class Convertor;
	u16 x;
	u16 y;
};

struct vec2u32
{
public:
	vec2u32(u32 x, u32 y) : x(x), y(y) {}

private:
	friend class Convertor;
	u32 x;
	u32 y;
};

class Convertor
{
private:
	friend struct i32;
	friend struct f32;

	static f32 i32tof32(i32 i)
	{
		return f32((f32::Raw)(i.value));
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
using math::u32;
using math::u64;
using math::vec2f32;
using math::vec2i32;
using math::vec2u16;
using math::vec2u32;

} // namespace ab


