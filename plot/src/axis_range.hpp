#ifndef AXIS_RANGE_HPP
#define AXIS_RANGE_HPP

#include <string>

namespace bright_lib{
namespace plot{

class AxisRange{
	public:
		bool hasLower, hasUpper;
		double lower, upper;

		AxisRange();
		void SetLower(double lower);
		void SetUpper(double upper);
		std::string GetScript();

}; /* class AxisRange */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* AXIS_RANGE_HPP */
