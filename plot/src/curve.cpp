#include "curve.hpp"

using namespace std;

namespace bright_lib{
namespace plot{

Curve::Curve(int _xCol, int _yCol)
	: xCol(_xCol), yCol(_yCol)
	, title("")
	, lineStyle()
{
}

void Curve::SetDataFile(string _dataFile){
	dataFile = _dataFile;
}

void Curve::SetTitle(string _title){
	title = _title;
}

string Curve::GetScript(){
	char ret[1000];
	sprintf(ret, "'%s' using ($%d):($%d) title '%s' w lp %s", dataFile.c_str(), xCol, yCol, title.c_str(), lineStyle.GetScript().c_str());
	return ret;
}

} /* namespace plot */
} /* namespace bright_lib */
