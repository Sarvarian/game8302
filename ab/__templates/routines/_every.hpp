
_TYPE_NAME(Raw value) : value_(value_) {}

_TYPE_NAME(_TYPE_NAME other) : value_(other.value_) {}

_TYPE_NAME() : value_(_DEFAULT_VALUE) {}

_TYPE_NAME add(_TYPE_NAME rhs) const
{
	return _TYPE_NAME(value_ + rhs.value_);
}

void add_inplace(_TYPE_NAME rhs) const
{
	value_ = value_ + rhs.value_;
}

_TYPE_NAME sub(_TYPE_NAME rhs) const
{
	return _TYPE_NAME(value_ - rhs.value_);
}

void sub_inplace(_TYPE_NAME rhs) const
{
	value_ = value_ - rhs.value_;
}

_TYPE_NAME mul(_TYPE_NAME rhs) const
{
	return _TYPE_NAME(value_ * rhs.value_);
}

void mul_inplace(_TYPE_NAME rhs) const
{
	value_ = value_ * rhs.value_;
}

_TYPE_NAME div(_TYPE_NAME rhs) const
{
	return _TYPE_NAME(value_ / rhs.value_);
}

void div_inplace(_TYPE_NAME rhs) const
{
	value_ = value_ / rhs.value_;
}

bool is_greater_then(_TYPE_NAME rhs) const
{
	return value_ > rhs.value_;
}

bool is_less_then(_TYPE_NAME rhs) const
{
	return value_ < rhs.value_;
}

bool is_equal_to(_TYPE_NAME rhs) const
{
	return value_ == rhs.value_;
}

bool is_greater_then_or_equal_to(_TYPE_NAME rhs) const
{
	return value_ >= rhs.value_;
}

bool is_less_then_or_equal_to(_TYPE_NAME rhs) const
{
	return value_ <= rhs.value_;
}
