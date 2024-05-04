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
inline float cpp_std_truncf(float arg) { return truncf(arg); }
inline double cpp_std_trunc(double arg) { return trunc(arg); }
inline long double cpp_std_truncl(long double arg) { return truncl(arg); }
} // namespace


//_GENERATE_CODE_HERE


} // namespace math
} // namespace ab

