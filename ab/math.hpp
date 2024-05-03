#pragma once

#ifdef pow
#endif

namespace ab
{
namespace math
{

namespace internal
{

namespace
{

inline float cpp_std_powf(float base, float exponent)
{
	return powf(base, exponent);
}

inline double cpp_std_pow(double base, double exponent)
{
	return pow(base, exponent);
}

inline long double cpp_std_powl(long double base, long double exponent)
{
	return powl(base, exponent);
}

inline float cpp_std_sqrtf(float arg)
{
	return sqrtf(arg);
}

inline double cpp_std_sqrt(double arg)
{
	return sqrt(arg);
}

inline long double cpp_std_sqrtl(long double arg)
{
	return sqrtl(arg);
}

inline float cpp_std_floorf(float arg)
{
	return floorf(arg);
}

inline double cpp_std_floor(double arg)
{
	return floor(arg);
}

inline long double cpp_std_floorl(long double arg)
{
	return floorl(arg);
}

} // namespace

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

	Type add(Type rhs) const
	{
		return Type(value + rhs.value);
	}

	void add_inplace(Type rhs) const
	{
		value = value + rhs.value;
	}

	Type sub(Type rhs) const
	{
		return Type(value - rhs.value);
	}

	void sub_inplace(Type rhs) const
	{
		value = value - rhs.value;
	}

	Type mul(Type rhs) const
	{
		return Type(value * rhs.value);
	}

	void mul_inplace(Type rhs) const
	{
		value = value * rhs.value;
	}

	Type div(Type rhs) const
	{
		return Type(value / rhs.value);
	}

	void div_inplace(Type rhs) const
	{
		value = value / rhs.value;
	}

	bool is_greater_then(Type rhs) const
	{
		return value > rhs.value;
	}

	bool is_less_then(Type rhs) const
	{
		return value < rhs.value;
	}

	bool is_equal_to(Type rhs) const
	{
		return value == rhs.value;
	}

	bool is_greater_then_or_equal_to(Type rhs) const
	{
		return value >= rhs.value;
	}

	bool is_less_then_or_equal_to(Type rhs) const
	{
		return value <= rhs.value;
	}

	Raw raw() const
	{
		return value;
	}

protected:

private:
	friend class Convertor;
	Raw value;

};

struct f32 : public TNumber<f32, primitives::raw_f32>
{
public:
	typedef f32 SecondBase;

	f32(Raw value) : Base(value) {}

	f32 pow(f32 exponent) const
	{
		return cpp_std_powf(raw(), exponent.raw());
	}

	f32 sqrt() const
	{
		return cpp_std_sqrtf(raw());
	}

	f32 floor() const
	{
		return cpp_std_floorf(raw());
	}

};

struct f64 : public TNumber<f64, primitives::raw_f64>
{
public:
	typedef f64 SecondBase;

	f64(Raw value) : Base(value) {}

	f64 pow(f64 exponent) const
	{
		return cpp_std_pow(raw(), exponent.raw());
	}

	f64 sqrt() const
	{
		return cpp_std_sqrt(raw());
	}

	f64 floor() const
	{
		return cpp_std_floor(raw());
	}

};

struct i32 : public TNumber<i32, primitives::raw_i32>
{
public:
	typedef i32 SecondBase;
	i32(Raw value) : Base(value) {}
};

struct u16 : public TNumber<u16, primitives::raw_u16>
{
public:
	typedef u16 SecondBase;
	u16(Raw value) : Base(value) {}
};

struct u32 : public TNumber<u32, primitives::raw_u32>
{
public:
	typedef u32 SecondBase;
	u32(Raw value) : Base(value) {}
};

struct u64 : public TNumber<u64, primitives::raw_u64>
{
public:
	typedef u64 SecondBase;
	u64(Raw value) : Base(value) {}
};

namespace
{

template<typename T, typename C>
struct TVector2
{
public:
	typedef TVector2<T, C> Base; // Base Type (TNumber Type)
	typedef T              Type; // Final Type
	typedef C              Comp; // Component Type

	TVector2(Comp x, Comp y) : x(x), y(y) {}
	TVector2(Type v) : x(v.x), y(v.y) {}
	TVector2() : x(0), y(0) {}

	Type add(Type rhs) const
	{
		return Type(x.add(rhs.x), y.add(rhs.y));
	}

	void add_inplace(Type rhs) const
	{
		x.add_inplace(rhs.x);
		y.add_inplace(rhs.y);
	}

	Type sub(Type rhs) const
	{
		return Type(x.sub(rhs.x), y.sub(rhs.y));
	}

	void sub_inplace(Type rhs) const
	{
		x.sub_inplace(rhs.x);
		y.sub_inplace(rhs.y);
	}

	Type scale(Comp rhs) const
	{
		return Type(x.mul(rhs), y.mul(rhs));
	}

	void scale_inplace(Comp rhs) const
	{
		x.mul_inplace(rhs);
		y.mul_inplace(rhs);
	}

	Comp length_squared() const
	{
		// --- (x * x) + (y * y) ---
		x = x.pow(2.0f);
		y = y.pow(2.0f);
		return x.add(y);
	}

	Comp length() const
	{
		return vec2_length_squared(x, y).sqrt();
	}

	Type normalize() const
	{
		Raw len = length();
		return Type(x.div(len), y.div(len));
	}

	void normalize_inplace() const
	{
		Raw len = length();
		x.div_inplace(len);
		y.div_inplace(len);
	}

	Type floor()
	{
		return Type(x.floor(), y.floor());
	}

private:
	friend class Convertor;
	Comp x;
	Comp y;

};

} // namespace

struct vec2f32 : public TVector2<vec2f32, f32>
{
public:
	typedef vec2f32 SecondBase;
	vec2f32(f32 x, f32 y) : Base(x, y) {}
	vec2f32() : Base(0, 0) {};
};

struct vec2i32 : public TVector2<vec2i32, i32>
{
public:
	typedef vec2i32 SecondBase;
	vec2i32(Comp x, Comp y) : Base(x, y) {}
};

struct vec2u16 : public TVector2<vec2u16, u16>
{
public:
	typedef vec2u16 SecondBase;
	vec2u16(Comp x, Comp y) : Base(x, y) {}
};

struct vec2u32 : public TVector2<vec2u32, u32>
{
public:
	typedef vec2u32 SecondBase;
	vec2u32(Comp x, Comp y) : Base(x, y) {}
};

class Convertor
{
public:

	inline static i32 f32_to_i32(f32 f)
	{
		return i32((i32::Raw)(f.value));
	}

	inline static f32 i32_to_f32(i32 i)
	{
		return f32((f32::Raw)(i.value));
	}

	inline static u32 i32_to_u32(i32 i)
	{
		return u32((u32::Raw)(i.value));
	}

	inline static i32 u64_to_i32(u64 i)
	{
		return i32((i32::Raw)(i.value));
	}

	inline static vec2i32 vec2f32_to_vec2i32(vec2f32 v)
	{
		return vec2i32(f32_to_i32(v.x), f32_to_i32(v.y));
	}

	inline static vec2f32 vec2i32_to_vec2f32(vec2i32 v)
	{
		return vec2f32(i32_to_f32(v.x), i32_to_f32(v.y));
	}

};

} // namespace internal

struct f32 : public internal::f32
{
	f32(Raw value) : SecondBase(value) {}
};

struct f64 : public internal::f64
{
	f64(Raw value) : SecondBase(value) {}
};

struct i32 : public internal::i32
{
	i32(Raw value) : SecondBase(value) {}
	internal::f32 to_f32() { return internal::Convertor::i32_to_f32(*this); }
};

struct u16 : public internal::u16
{
	u16(Raw value) : SecondBase(value) {}
};

struct u32 : public internal::u32
{
	u32(Raw value) : SecondBase(value) {}
};

struct u64 : public internal::u64
{
	u64(Raw value) : SecondBase(value) {}
	internal::i32 to_i32() { internal::Convertor::u64_to_i32(*this); }
};

struct vec2f32 : public internal::vec2f32
{
	vec2f32(SecondBase value) : SecondBase(value) {}
	vec2f32(Comp x, Comp y) : SecondBase(x, y) {}
	vec2f32 floor() { return internal::vec2f32::floor(); }
	internal::vec2i32 to_vec2i32() { return internal::Convertor::vec2f32_to_vec2i32(*this); }
};

struct vec2i32 : public internal::vec2i32
{
	vec2i32(SecondBase value) : SecondBase(value) {}
	vec2i32(Comp x, Comp y) : SecondBase(x, y) {}
	internal::vec2f32 to_vec2f32() { return internal::Convertor::vec2i32_to_vec2f32(*this); }
};

struct vec2u16 : public internal::vec2u16
{
	vec2u16(SecondBase value) : SecondBase(value) {}
	vec2u16(Comp x, Comp y) : SecondBase(x, y) {}
};

struct vec2u32 : public internal::vec2u32
{
	vec2u32(SecondBase value) : SecondBase(value) {}
	vec2u32(Comp x, Comp y) : SecondBase(x, y) {}
};

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


