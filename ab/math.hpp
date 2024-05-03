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

};

struct i32 : public TNumber<i32, primitives::raw_i32>
{
public:
	i32(Raw value) : Base(value) {}

	f32 to_float();

};

struct u16 : public TNumber<u16, primitives::raw_u16>
{
public:
	u16(Raw value) : Base(value) {}
};

struct u32 : public TNumber<u32, primitives::raw_u32>
{
public:
	u32(Raw value) : Base(value) {}
};

struct u64 : public TNumber<u64, primitives::raw_u64>
{
public:
	u64(Raw value) : Base(value) {}
};

namespace
{

template<typename T, typename R>
struct TVector2
{
public:
	typedef TVector2<T, R> Base; // Base Type (TNumber Type)
	typedef T              Type; // Final Type
	typedef R               Raw; // Raw Type

	TVector2(Raw x, Raw y) : x(x), y(y) {}
	TVector2(Type v) : x(v.x), y(v.y) {}
	TVector2() : x(0), y(0) {}

	Type add(Type rhs)
	{
		return Type(x.add(rhs.x), y.add(rhs.y));
	}

	void add_inplace(Type rhs)
	{
		x.add_inplace(rhs.x);
		y.add_inplace(rhs.y);
	}

	Type sub(Type rhs)
	{
		return Type(x.sub(rhs.x), y.sub(rhs.y));
	}

	void sub_inplace(Type rhs)
	{
		x.sub_inplace(rhs.x);
		y.sub_inplace(rhs.y);
	}

	Type mul(Raw rhs)
	{
		return Type(x.mul(rhs), y.mul(rhs));
	}

	void mul_inplace(Raw rhs)
	{
		x.mul_inplace(rhs);
		y.mul_inplace(rhs);
	}

	Raw length_squared()
	{
		// --- (x * x) + (y * y) ---
		x = x.mul(x);
		y = y.mul(y);
		return x.add(y);
	}

	Raw length()
	{
		return vec2_length_squared(x, y).sqrt();
	}

	Type normalize()
	{
		Raw len = length();
		return Type(x.div(len), y.div(len));
	}

	void normalize_inplace()
	{
		Raw len = length();
		x.div_inplace(len);
		y.div_inplace(len);
	}

private:
	friend class Convertor;
	Raw x;
	Raw y;

};

} // namespace

struct vec2f32 : public TVector2<vec2f32, f32>
{
public:
	vec2f32(f32 x, f32 y) : Base(x, y) {}
	vec2f32() : Base(0, 0) {};
};

struct vec2i32 : public TVector2<vec2i32, i32>
{
public:
	vec2i32(Raw x, Raw y) : Base(x, y) {}
};

struct vec2u16 : public TVector2<vec2u16, u16>
{
public:
	vec2u16(Raw x, Raw y) : Base(x, y) {}
};

struct vec2u32 : public TVector2<vec2u32, u32>
{
public:
	vec2u32(Raw x, Raw y) : Base(x, y) {}
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


