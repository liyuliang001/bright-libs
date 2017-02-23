#include "curve.hpp"

using namespace std;

namespace bright_lib{
namespace plot{

Curve::Curve(int _xCol, int _yCol)
	: xCol(_xCol), yCol(_yCol)
	, xScale(1.0), yScale(1.0)
	, title("")
	, lineStyle()
{
}

void Curve::SetXScale(double s){
	xScale = s;
}
void Curve::SetYScale(double s){
	yScale = s;
}

void Curve::SetDataFile(string _dataFile){
	dataFile = _dataFile;
}

void Curve::SetTitle(string _title){
	title = _title;
}

string Curve::GetScript(){
	char ret[1000];
	string with;
	if (lineStyle.hasPoint && lineStyle.hasLine)
		with = "lp";
	else if (lineStyle.hasPoint)
		with = "p";
	else if (lineStyle.hasLine)
		with = "l";
	sprintf(ret, "'%s' using ($%d*%lf):($%d*%lf) title '%s' w %s %s", dataFile.c_str(), xCol, xScale, yCol, yScale, title.c_str(), with.c_str(), lineStyle.GetScript().c_str());
	return ret;
}

} /* namespace plot */
} /* namespace bright_lib */
