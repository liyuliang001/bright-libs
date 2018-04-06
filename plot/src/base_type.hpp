#ifndef BRIGHT_LIB__PLOT__BASE_TYPE_HPP
#define BRIGHT_LIB__PLOT__BASE_TYPE_HPP

#include <string>

namespace bright_lib{
namespace plot{

class BaseType{
	public:
		virtual std::string GetScript() = 0;
}; /* class BaseType */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* BRIGHT_LIB__PLOT__BASE_TYPE_HPP */
