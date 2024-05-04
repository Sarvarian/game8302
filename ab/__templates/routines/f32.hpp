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