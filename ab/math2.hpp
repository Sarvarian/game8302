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

namespace
{

/// @brief 
/// @tparam T FinalType
/// @tparam R RawType
template<typename T, typename R>
class TNumber
{
public:
	typedef TNumber<T, R> Base; // Base Type (TNumber Type)
	typedef T             Type; // Final Type
	typedef R              Raw; // Raw Type

	TNumber(Raw v) : value(v) {}
	TNumber(Type v) : value(v.value) {}

	Type add(Type rhs)
	{
		return f32(value + rhs.value);
	}

	Type mul(Type rhs)
	{
		return f32(value * rhs.value);
	}

protected:
	Raw get_raw()
	{
		return value;
	}

private:
	friend class Convertor;
	Raw value = 0;

};

} // namespace

class f32 : public TNumber<f32, primitives::raw_f32>
{
public:
	f32(Raw value) : Base(value) {}

	f32 sqrt()
	{
		return sqrtf(get_raw());
	}

private:
};

} // namespace math

using math::f32;


} // namespace ab


