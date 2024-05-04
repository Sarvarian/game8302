
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