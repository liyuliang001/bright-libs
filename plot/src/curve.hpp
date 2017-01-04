#ifndef CURVE_HPP
#define CURVE_HPP

#include <string>
#include "base_type.hpp"
#include "axis_range.hpp"
#include "line_style.hpp"

namespace bright_lib{
namespace plot{

class Curve: public BaseType{
	public:
		int xCol, yCol;
		std::string dataFile;
		std::string title;
		LineStyle lineStyle;
		
		Curve(int _xCol, int _yCol);
		void SetDataFile(std::string _dataFile);
		void SetTitle(std::string _title);
		virtual std::string GetScript();
}; /* class Curve */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* CURVE_HPP */
