#ifndef _BRIGHT_LIB__RAND__RAND_FLOAT_HPP
#define _BRIGHT_LIB__RAND__RAND_FLOAT_HPP

#include <cstdlib>

namespace bright_lib{
namespace random{

static inline double rand_double(){
	return ::rand() / double(RAND_MAX);
}

}
}

#endif /* _BRIGHT_LIB__RAND__RAND_FLOAT_HPP */
