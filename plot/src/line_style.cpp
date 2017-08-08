#include "line_style.hpp"

using namespace std;

namespace bright_lib{
namespace plot{

LineStyle::LineStyle()
	: lt(1), lc(), lw(1.0), pt(1), ps(1.0)
	, hasLine(true), hasPoint(true)
{
}

void LineStyle::SetHasLine(bool _hasLine){
	hasLine = _hasLine;
}
void LineStyle::SetHasPoint(bool _hasPoint){
	hasPoint = _hasPoint;
}

void LineStyle::SetLineType(int t){
	lt = t;
}

void LineStyle::SetLineColor(int c){
	lc.Set(c);
}

void LineStyle::SetLineColor(std::string c){
	lc.Set(c);
}

void LineStyle::SetDashType(int t){
	dt = t;
}

void LineStyle::SetLineWidth(double w){
	lw = w;
}

void LineStyle::SetPointType(int t){
	pt = t;
}

void LineStyle::SetPointSize(double s){
	ps = s;
}

string LineStyle::GetScript(){
	string res = "";
	if (hasLine)
		res += "lt " + to_string(lt) + " " + lc.GetScript() + " dt " + to_string(dt) + " lw " + to_string(lw);
	else  // lc is required for points
		res += lc.GetScript();
	if (hasPoint)
		res += " pt " + to_string(pt) + " ps " + to_string(ps);
	return res;
}

} /* namespace plot */
} /* namespace bright_lib */
