
f64 pow(f64 exponent) const
{
	return cpp_std_pow(raw(), exponent.raw());
}

void pow_inplace(f64 exponent) const
{
	set_raw(cpp_std_pow(raw(), exponent.raw()));
}

f64 sqrt() const
{
	return cpp_std_sqrt(raw());
}

void sqrt() const
{
	set_raw(cpp_std_sqrt(raw()));
}

f64 floor() const
{
	return cpp_std_floor(raw());
}

void floor() const
{
	set_raw(cpp_std_floor(raw()));
}

f64 trunc() const
{
	return cpp_std_trunc(raw());
}

void trunc() const
{
	set_raw(cpp_std_trunc(raw()));
}
