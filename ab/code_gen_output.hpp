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



struct f32
{
public:
	typedef float Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct f64
{
public:
	typedef double Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct i8
{
public:
	typedef Sint8 Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct i16
{
public:
	typedef Sint16 Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct i32
{
public:
	typedef Sint32 Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct i64
{
public:
	typedef Sint64 Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct u8
{
public:
	typedef Uint8 Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct u16
{
public:
	typedef Uint16 Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct u32
{
public:
	typedef Uint32 Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct u64
{
public:
	typedef Uint64 Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct isize
{
public:
	typedef intptr_t Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};

struct usize
{
public:
	typedef uintptr_t Raw;


	//_GENERATE_ROUTINES_HERE


	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

	void set_raw(Raw new_value)
	{
		value_ = new_value;
	}

};



} // namespace math
} // namespace ab

