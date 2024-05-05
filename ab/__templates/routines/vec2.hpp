
_COMP_NAME dot(_TYPE_NAME other) const
{
	// --- (a.x * b.x) + (a.y * b.y) ---
	lhs = x.mul(other.x);
	rhs = y.mul(other.y);
	return lhs.add(rhs);
}

_COMP_NAME length_squared() const
{
	return dot(*this)
}

_COMP_NAME length() const
{
	return length_squared(x, y).sqrt();
}

_COMP_NAME normalize() const
{
	_COMP_NAME len = length();
	return _TYPE_NAME(x.div(len), y.div(len));
}

void normalize_inplace() const
{
	_COMP_NAME len = length();
	x.div_inplace(len);
	y.div_inplace(len);
}

_TYPE_NAME floor() const
{
	return _TYPE_NAME(x.floor(), y.floor());
}

_TYPE_NAME floor_inplace() const
{
	x.floor_inplace();
	y.floor_inplace();
}


