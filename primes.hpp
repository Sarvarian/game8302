#pragma once

namespace ab
{
	namespace primitives
	{

		typedef Sint8      i8;
		typedef Sint16     i16;
		typedef Sint32     i32;
		typedef Sint64     i64;
		typedef Uint8      u8;
		typedef Uint16     u16;
		typedef Uint32     u32;
		typedef Uint64     u64;

		typedef intptr_t   isize;
		typedef uintptr_t  usize;

#define ptr   void*
#define null  NULL

		// #define and   &&
		// #define or    ||
		// #define not   !

#define sub
#define proc  void
#define func

	} // space: primitives

	using namespace primitives;

} // space: ab
