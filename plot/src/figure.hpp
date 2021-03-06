#ifndef BRIGHT_LIB__PLOT__FIGURE_HPP
#define BRIGHT_LIB__PLOT__FIGURE_HPP

#include <string>
#include <vector>
#include "axis_range.hpp"
#include "base_type.hpp"
#include "curve.hpp"

namespace bright_lib{
namespace plot{
	
class Figure{
	public:
		bool logx, logy;
		std::string outputName;
		std::string xLabel, yLabel;
		std::string legendPos;
		AxisRange xRange, yRange;
		std::string xTics, yTics;
		std::vector<BaseType*> curves;

		Figure();
		void SetLogX(bool _logx = true);
		void SetLogY(bool _logy = true);
		void SetOutputName(std::string name);
		void SetXLabel(std::string _xLabel);
		void SetYLabel(std::string _yLabel);
		void SetXUpper(double xUpper);
		void SetXLower(double xLower);
		void SetYUpper(double yUpper);
		void SetYLower(double yLower);
		void SetXTics(std::string s);
		void SetYTics(std::string s);

		Curve* AddCurve(int xCol, int yCol);
		std::string GetScript();
		void Plot(std::string scriptName = "");
}; /* class Figure */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* BRIGHT_LIB__PLOT__FIGURE_HPP */
