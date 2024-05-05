
_TYPE_NAME(_COMP_NAME x, _COMP_NAME y) : x_(x), y_(y) {}
_TYPE_NAME() : x_(0), y_(0) {}

_TYPE_NAME add(_TYPE_NAME rhs) const
{
	return _TYPE_NAME(x_.add(rhs.x_), y_.add(rhs.y_));
}

void add_inplace(_TYPE_NAME rhs)
{
	x_.add_inplace(rhs.x_);
	y_.add_inplace(rhs.y_);
}

_TYPE_NAME sub(_TYPE_NAME rhs) const
{
	return _TYPE_NAME(x_.sub(rhs.x_), y_.sub(rhs.y_));
}

void sub_inplace(Type rhs)
{
	x_.sub_inplace(rhs.x_);
	y_.sub_inplace(rhs.y_);
}

_TYPE_NAME scale(_COMP_NAME rhs) const
{
	return _TYPE_NAME(x_.mul(rhs), y_.mul(rhs));
}

void scale_inplace(_COMP_NAME rhs)
{
	x_.mul_inplace(rhs);
	y_.mul_inplace(rhs);
}

_COMP_NAME dot(_TYPE_NAME other) const
{
	// --- (a.x * b.x) + (a.y * b.y) ---
	lhs = x_.mul(other.x_);
	rhs = y_.mul(other.y_);
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
	return _TYPE_NAME(x_.div(len), y_.div(len));
}

void normalize_inplace()
{
	_COMP_NAME len = length();
	x_.div_inplace(len);
	y_.div_inplace(len);
}

_TYPE_NAME floor() const
{
	return _TYPE_NAME(x_.floor(), y_.floor());
}

_TYPE_NAME floor_inplace()
{
	x_.floor_inplace();
	y_.floor_inplace();
}


