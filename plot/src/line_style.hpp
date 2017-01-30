#ifndef LINE_STYLE_HPP
#define LINE_STYLE_HPP

#include "color.hpp"

namespace bright_lib{
namespace plot{

class LineStyle{
	public:
		int lt; // line type
		Color lc; // line color
		double lw; // line width
		int pt; // point type
		double ps; // point size

		LineStyle();
		void SetLineType(int t);
		void SetLineColor(int c);
		void SetLineColor(std::string c);
		void SetlineWidth(double w);
		void SetPointType(int t);
		void SetPointSize(double s);
		std::string GetScript();
}; /* class LineStyle */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* LINE_STYLE_HPP */