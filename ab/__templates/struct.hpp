
struct _TYPE_NAME
{
public:
	typedef _RAW_TYPE Raw;


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
