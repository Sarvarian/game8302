// This file is generated by python scripts and some templates .

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

struct f32;
struct f64;
struct i8;
struct i16;
struct i32;
struct i64;
struct u8;
struct u16;
struct u32;
struct u64;
struct isize;
struct usize;

struct f32
{
public:
	typedef float Raw;

	f32(Raw value) : value_(value_) {}

	f32(f32 other) : value_(other.value_) {}

	f32() : value_(0.0f) {}

	f32 add(f32 rhs) const
	{
		return f32(value_ + rhs.value_);
	}

	void add_inplace(f32 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	f32 sub(f32 rhs) const
	{
		return f32(value_ - rhs.value_);
	}

	void sub_inplace(f32 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	f32 mul(f32 rhs) const
	{
		return f32(value_ * rhs.value_);
	}

	void mul_inplace(f32 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	f32 div(f32 rhs) const
	{
		return f32(value_ / rhs.value_);
	}

	void div_inplace(f32 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(f32 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(f32 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(f32 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(f32 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(f32 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 pow(f32 exponent) const
	{
		return cpp_std_powf(value_, exponent.value_);
	}

	void pow_inplace(f32 exponent) const
	{
		value_ = cpp_std_powf(value_, exponent.value_);
	}

	f32 sqrt() const
	{
		return cpp_std_sqrtf(value_);
	}

	void sqrt_inplace() const
	{
		value_ = cpp_std_sqrtf(value_);
	}

	f32 floor() const
	{
		return cpp_std_floorf(value_);
	}

	void floor_inplace() const
	{
		value_ = cpp_std_floorf(value_);
	}

	f32 trunc() const
	{
		return cpp_std_truncf(value_);
	}

	void trunc_inplace() const
	{
		value_ = cpp_std_truncf(value_);
	}

	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct f64
{
public:
	typedef double Raw;

	f64(Raw value) : value_(value_) {}

	f64(f64 other) : value_(other.value_) {}

	f64() : value_(0.0) {}

	f64 add(f64 rhs) const
	{
		return f64(value_ + rhs.value_);
	}

	void add_inplace(f64 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	f64 sub(f64 rhs) const
	{
		return f64(value_ - rhs.value_);
	}

	void sub_inplace(f64 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	f64 mul(f64 rhs) const
	{
		return f64(value_ * rhs.value_);
	}

	void mul_inplace(f64 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	f64 div(f64 rhs) const
	{
		return f64(value_ / rhs.value_);
	}

	void div_inplace(f64 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(f64 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(f64 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(f64 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(f64 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(f64 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f64 pow(f64 exponent) const
	{
		return cpp_std_pow(value_, exponent.value_);
	}

	void pow_inplace(f64 exponent) const
	{
		value_ = cpp_std_pow(value_, exponent.value_);
	}

	f64 sqrt() const
	{
		return cpp_std_sqrt(value_);
	}

	void sqrt() const
	{
		value_ = cpp_std_sqrt(value_);
	}

	f64 floor() const
	{
		return cpp_std_floor(value_);
	}

	void floor() const
	{
		value_ = cpp_std_floor(value_);
	}

	f64 trunc() const
	{
		return cpp_std_trunc(value_);
	}

	void trunc() const
	{
		value_ = cpp_std_trunc(value_);
	}

	f32 to_f32() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct i8
{
public:
	typedef Sint8 Raw;

	i8(Raw value) : value_(value_) {}

	i8(i8 other) : value_(other.value_) {}

	i8() : value_(0) {}

	i8 add(i8 rhs) const
	{
		return i8(value_ + rhs.value_);
	}

	void add_inplace(i8 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	i8 sub(i8 rhs) const
	{
		return i8(value_ - rhs.value_);
	}

	void sub_inplace(i8 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	i8 mul(i8 rhs) const
	{
		return i8(value_ * rhs.value_);
	}

	void mul_inplace(i8 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	i8 div(i8 rhs) const
	{
		return i8(value_ / rhs.value_);
	}

	void div_inplace(i8 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(i8 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(i8 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(i8 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(i8 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(i8 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct i16
{
public:
	typedef Sint16 Raw;

	i16(Raw value) : value_(value_) {}

	i16(i16 other) : value_(other.value_) {}

	i16() : value_(0) {}

	i16 add(i16 rhs) const
	{
		return i16(value_ + rhs.value_);
	}

	void add_inplace(i16 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	i16 sub(i16 rhs) const
	{
		return i16(value_ - rhs.value_);
	}

	void sub_inplace(i16 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	i16 mul(i16 rhs) const
	{
		return i16(value_ * rhs.value_);
	}

	void mul_inplace(i16 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	i16 div(i16 rhs) const
	{
		return i16(value_ / rhs.value_);
	}

	void div_inplace(i16 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(i16 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(i16 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(i16 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(i16 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(i16 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct i32
{
public:
	typedef Sint32 Raw;

	i32(Raw value) : value_(value_) {}

	i32(i32 other) : value_(other.value_) {}

	i32() : value_(0) {}

	i32 add(i32 rhs) const
	{
		return i32(value_ + rhs.value_);
	}

	void add_inplace(i32 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	i32 sub(i32 rhs) const
	{
		return i32(value_ - rhs.value_);
	}

	void sub_inplace(i32 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	i32 mul(i32 rhs) const
	{
		return i32(value_ * rhs.value_);
	}

	void mul_inplace(i32 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	i32 div(i32 rhs) const
	{
		return i32(value_ / rhs.value_);
	}

	void div_inplace(i32 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(i32 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(i32 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(i32 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(i32 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(i32 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct i64
{
public:
	typedef Sint64 Raw;

	i64(Raw value) : value_(value_) {}

	i64(i64 other) : value_(other.value_) {}

	i64() : value_(0) {}

	i64 add(i64 rhs) const
	{
		return i64(value_ + rhs.value_);
	}

	void add_inplace(i64 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	i64 sub(i64 rhs) const
	{
		return i64(value_ - rhs.value_);
	}

	void sub_inplace(i64 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	i64 mul(i64 rhs) const
	{
		return i64(value_ * rhs.value_);
	}

	void mul_inplace(i64 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	i64 div(i64 rhs) const
	{
		return i64(value_ / rhs.value_);
	}

	void div_inplace(i64 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(i64 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(i64 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(i64 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(i64 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(i64 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct u8
{
public:
	typedef Uint8 Raw;

	u8(Raw value) : value_(value_) {}

	u8(u8 other) : value_(other.value_) {}

	u8() : value_(0) {}

	u8 add(u8 rhs) const
	{
		return u8(value_ + rhs.value_);
	}

	void add_inplace(u8 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	u8 sub(u8 rhs) const
	{
		return u8(value_ - rhs.value_);
	}

	void sub_inplace(u8 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	u8 mul(u8 rhs) const
	{
		return u8(value_ * rhs.value_);
	}

	void mul_inplace(u8 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	u8 div(u8 rhs) const
	{
		return u8(value_ / rhs.value_);
	}

	void div_inplace(u8 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(u8 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(u8 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(u8 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(u8 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(u8 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct u16
{
public:
	typedef Uint16 Raw;

	u16(Raw value) : value_(value_) {}

	u16(u16 other) : value_(other.value_) {}

	u16() : value_(0) {}

	u16 add(u16 rhs) const
	{
		return u16(value_ + rhs.value_);
	}

	void add_inplace(u16 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	u16 sub(u16 rhs) const
	{
		return u16(value_ - rhs.value_);
	}

	void sub_inplace(u16 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	u16 mul(u16 rhs) const
	{
		return u16(value_ * rhs.value_);
	}

	void mul_inplace(u16 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	u16 div(u16 rhs) const
	{
		return u16(value_ / rhs.value_);
	}

	void div_inplace(u16 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(u16 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(u16 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(u16 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(u16 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(u16 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct u32
{
public:
	typedef Uint32 Raw;

	u32(Raw value) : value_(value_) {}

	u32(u32 other) : value_(other.value_) {}

	u32() : value_(0) {}

	u32 add(u32 rhs) const
	{
		return u32(value_ + rhs.value_);
	}

	void add_inplace(u32 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	u32 sub(u32 rhs) const
	{
		return u32(value_ - rhs.value_);
	}

	void sub_inplace(u32 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	u32 mul(u32 rhs) const
	{
		return u32(value_ * rhs.value_);
	}

	void mul_inplace(u32 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	u32 div(u32 rhs) const
	{
		return u32(value_ / rhs.value_);
	}

	void div_inplace(u32 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(u32 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(u32 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(u32 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(u32 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(u32 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u64 to_u64() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct u64
{
public:
	typedef Uint64 Raw;

	u64(Raw value) : value_(value_) {}

	u64(u64 other) : value_(other.value_) {}

	u64() : value_(0) {}

	u64 add(u64 rhs) const
	{
		return u64(value_ + rhs.value_);
	}

	void add_inplace(u64 rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	u64 sub(u64 rhs) const
	{
		return u64(value_ - rhs.value_);
	}

	void sub_inplace(u64 rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	u64 mul(u64 rhs) const
	{
		return u64(value_ * rhs.value_);
	}

	void mul_inplace(u64 rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	u64 div(u64 rhs) const
	{
		return u64(value_ / rhs.value_);
	}

	void div_inplace(u64 rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(u64 rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(u64 rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(u64 rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(u64 rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(u64 rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	isize to_isize() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct isize
{
public:
	typedef intptr_t Raw;

	isize(Raw value) : value_(value_) {}

	isize(isize other) : value_(other.value_) {}

	isize() : value_(0) {}

	isize add(isize rhs) const
	{
		return isize(value_ + rhs.value_);
	}

	void add_inplace(isize rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	isize sub(isize rhs) const
	{
		return isize(value_ - rhs.value_);
	}

	void sub_inplace(isize rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	isize mul(isize rhs) const
	{
		return isize(value_ * rhs.value_);
	}

	void mul_inplace(isize rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	isize div(isize rhs) const
	{
		return isize(value_ / rhs.value_);
	}

	void div_inplace(isize rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(isize rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(isize rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(isize rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(isize rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(isize rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	usize to_usize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};
struct usize
{
public:
	typedef uintptr_t Raw;

	usize(Raw value) : value_(value_) {}

	usize(usize other) : value_(other.value_) {}

	usize() : value_(0) {}

	usize add(usize rhs) const
	{
		return usize(value_ + rhs.value_);
	}

	void add_inplace(usize rhs) const
	{
		value_ = value_ + rhs.value_;
	}

	usize sub(usize rhs) const
	{
		return usize(value_ - rhs.value_);
	}

	void sub_inplace(usize rhs) const
	{
		value_ = value_ - rhs.value_;
	}

	usize mul(usize rhs) const
	{
		return usize(value_ * rhs.value_);
	}

	void mul_inplace(usize rhs) const
	{
		value_ = value_ * rhs.value_;
	}

	usize div(usize rhs) const
	{
		return usize(value_ / rhs.value_);
	}

	void div_inplace(usize rhs) const
	{
		value_ = value_ / rhs.value_;
	}

	bool is_greater_then(usize rhs) const
	{
		return value_ > rhs.value_;
	}

	bool is_less_then(usize rhs) const
	{
		return value_ < rhs.value_;
	}

	bool is_equal_to(usize rhs) const
	{
		return value_ == rhs.value_;
	}

	bool is_greater_then_or_equal_to(usize rhs) const
	{
		return value_ >= rhs.value_;
	}

	bool is_less_then_or_equal_to(usize rhs) const
	{
		return value_ <= rhs.value_;
	}

	f32 to_f32() const;
	f64 to_f64() const;
	i8 to_i8() const;
	i16 to_i16() const;
	i32 to_i32() const;
	i64 to_i64() const;
	u8 to_u8() const;
	u16 to_u16() const;
	u32 to_u32() const;
	u64 to_u64() const;
	isize to_isize() const;

	Raw raw() const
	{
		return value_;
	}

private:
	Raw value_;

};


} // namespace math
} // namespace ab
