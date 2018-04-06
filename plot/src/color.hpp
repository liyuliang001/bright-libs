#ifndef BRIGHT_LIB__PLOT__COLOR_HPP
#define BRIGHT_LIB__PLOT__COLOR_HPP

#include <string>

namespace bright_lib{
namespace plot{

class Color{
	public:
		enum Type{
			Num = 0,
			Rgb = 1
		};
		Type type;
		int number;
		std::string rgb;

		Color();
		std::string GetScript();
		void SetNum(int _number);
		void SetRgb(std::string _rgb);
		void Set(int _number);
		void Set(std::string _rgb);
}; /* class Color */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* BRIGHT_LIB__PLOT__COLOR_HPP */
