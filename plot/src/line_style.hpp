#ifndef LINE_STYLE_HPP
#define LINE_STYLE_HPP

#include "color.hpp"

namespace bright_lib{
namespace plot{

class LineStyle{
	public:
		int lt; // line type
		Color lc; // line color
		int dt; // dath type
		double lw; // line width
		int pt; // point type
		double ps; // point size
		bool hasLine, hasPoint;

		LineStyle();
		void SetHasLine(bool _hasLine = false);
		void SetHasPoint(bool _hasPoint = false);
		void SetLineType(int t);
		void SetLineColor(int c);
		void SetLineColor(std::string c);
		void SetDashType(int t);
		void SetLineWidth(double w);
		void SetPointType(int t);
		void SetPointSize(double s);
		std::string GetScript();
}; /* class LineStyle */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* LINE_STYLE_HPP */
