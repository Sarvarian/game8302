
_TYPE_NAME(Raw value) : value_(value) {}

_TYPE_NAME(_TYPE_NAME other) : value_(other.value_) {}

_TYPE_NAME() : value_(_DEFAULT_VALUE) {}

_TYPE_NAME add(_TYPE_NAME rhs) const
{
	return _TYPE_NAME(value + rhs.value);
}

void add_inplace(_TYPE_NAME rhs) const
{
	value = value + rhs.value;
}

_TYPE_NAME sub(_TYPE_NAME rhs) const
{
	return Type(value - rhs.value);
}

void sub_inplace(_TYPE_NAME rhs) const
{
	value = value - rhs.value;
}

_TYPE_NAME mul(_TYPE_NAME rhs) const
{
	return Type(value * rhs.value);
}

void mul_inplace(_TYPE_NAME rhs) const
{
	value = value * rhs.value;
}

_TYPE_NAME div(_TYPE_NAME rhs) const
{
	return Type(value / rhs.value);
}

void div_inplace(_TYPE_NAME rhs) const
{
	value = value / rhs.value;
}

bool is_greater_then(_TYPE_NAME rhs) const
{
	return value > rhs.value;
}

bool is_less_then(_TYPE_NAME rhs) const
{
	return value < rhs.value;
}

bool is_equal_to(_TYPE_NAME rhs) const
{
	return value == rhs.value;
}

bool is_greater_then_or_equal_to(_TYPE_NAME rhs) const
{
	return value >= rhs.value;
}

bool is_less_then_or_equal_to(_TYPE_NAME rhs) const
{
	return value <= rhs.value;
}
