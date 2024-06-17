#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cmath>

#include "vec2.h"

#define DBG(x) std::cout << "dbg##x" << std::endl;

namespace util {
    vec2 get_random_gradient(int x);

	std::string read_to_string(const char *filename); 

    double interpolate(double a, double b, double t);
};


#endif /* UTIL_H */
