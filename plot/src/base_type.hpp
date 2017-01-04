#ifndef BASE_TYPE_HPP
#define BASE_TYPE_HPP

#include <string>

namespace bright_lib{
namespace plot{

class BaseType{
	public:
		virtual std::string GetScript() = 0;
}; /* class BaseType */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* BASE_TYPE_HPP */
