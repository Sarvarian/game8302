
f32 pow(f32 exponent) const
{
	return cpp_std_powf(raw(), exponent.raw());
}

void pow_inplace(f32 exponent) const
{
	set_raw(cpp_std_powf(raw(), exponent.raw()));
}

f32 sqrt() const
{
	return cpp_std_sqrtf(raw());
}

void sqrt_inplace() const
{
	set_raw(cpp_std_sqrtf(raw()));
}

f32 floor() const
{
	return cpp_std_floorf(raw());
}

void floor_inplace() const
{
	set_raw(cpp_std_floorf(raw()));
}

f32 trunc() const
{
	return cpp_std_truncf(raw());
}

void trunc_inplace() const
{
	set_raw(cpp_std_truncf(raw()));
}

