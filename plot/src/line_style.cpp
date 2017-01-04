#include "line_style.hpp"

using namespace std;

namespace bright_lib{
namespace plot{

LineStyle::LineStyle()
	: lt(1), lc(), lw(1.0), pt(1), ps(1.0)
{
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

void LineStyle::SetlineWidth(double w){
	lw = w;
}

void LineStyle::SetPointType(int t){
	pt = t;
}

void LineStyle::SetPointSize(double s){
	ps = s;
}

string LineStyle::GetScript(){
	return "lt " + to_string(lt) + " " + lc.GetScript() + " lw " + to_string(lw) + " pt " + to_string(pt) + " ps " + to_string(ps);
}

} /* namespace plot */
} /* namespace bright_lib */
