#include "axis_range.hpp"

using namespace std;

namespace bright_lib{
namespace plot{

AxisRange::AxisRange(){
	hasLower = hasUpper = false;
}
void AxisRange::SetLower(double lower){
	this->hasLower = true;
	this->lower = lower;
}
void AxisRange::SetUpper(double upper){
	this->hasUpper = true;
	this->upper = upper;
}
string AxisRange::GetScript(){
	string res = "[";
	if (hasLower)
		res += to_string(lower);
	res += ":";
	if (hasUpper)
		res += to_string(upper);
	res += "]";
	return res;
}

} /* namespace plot */
} /* namespace bright_lib */
