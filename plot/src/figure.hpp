#ifndef FIGURE_HPP
#define FIGURE_HPP

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

		Curve* AddCurve(int xCol, int yCol);
		std::string GetScript();
		void Plot(std::string scriptName = "");
}; /* class Figure */

} /* namespace plot */
} /* namespace bright_lib */
#endif /* FIGURE_HPP */
