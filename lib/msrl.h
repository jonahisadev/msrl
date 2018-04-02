#ifndef MSRL_H
#define MSRL_H

#include <stdio.h>
#include <stdlib.h>

#define assert(x) if (!(x)) { fprintf(stderr, "Assertion failure (%s:%d)", __FILE__, __LINE__); exit(1); }

#include "msrl_mem.h"

#endif // MSRL_H