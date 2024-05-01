#pragma once

#include <stdio.h>
#include <stdlib.h>

#if defined(_MSC_VER) && (_MSC_VER < 1300)
#define OLD_MSVC
#endif

#ifdef OLD_MSVC
#include "SDL_stdinc.h"
#else
#include "SDL.h"
#endif

#ifdef OLD_MSVC
#ifdef _WIN64
typedef unsigned __int64 size_t;
typedef __int64          ptrdiff_t;
typedef __int64          intptr_t;
#else
typedef unsigned int     size_t;
typedef int              ptrdiff_t;
typedef int              intptr_t;
#endif
#endif

#include "primes.hpp"
