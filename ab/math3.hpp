#pragma once

namespace ab
{
namespace math
{

namespace
{
inline float cpp_std_powf(float base, float exponent) { return powf(base, exponent); }
inline double cpp_std_pow(double base, double exponent) { return pow(base, exponent); }
inline long double cpp_std_powl(long double base, long double exponent) { return powl(base, exponent); }
inline float cpp_std_sqrtf(float arg) { return sqrtf(arg); }
inline double cpp_std_sqrt(double arg) { return sqrt(arg); }
inline long double cpp_std_sqrtl(long double arg) { return sqrtl(arg); }
inline float cpp_std_floorf(float arg) { return floorf(arg); }
inline double cpp_std_floor(double arg) { return floor(arg); }
inline long double cpp_std_floorl(long double arg) { return floorl(arg); }
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



} // namespace math
} // namespace ab

