#include "pch.hpp"

#include "ab/code_gen_output.hpp"

using namespace ab;
using namespace ab::math;

int cmdline_argc;
char** cmdline_argv;

int main(int argc, char** argv)
{
	cmdline_argc = argc;
	cmdline_argv = argv;

	f32 x = 0.0f;

	x = 3;

	f32 y = x;

	y = x.mul(y);

	printf("Number is: %f", y.raw());

	return 0;
}


