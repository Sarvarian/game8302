
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

};
