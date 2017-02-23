#include <cstdlib>
#include <fstream>
#include "figure.hpp"
using namespace std;

namespace bright_lib{
namespace plot{

Figure::Figure()
	: logx(false), logy(false)
	, outputName("unnamed.pdf"), xLabel("x"), yLabel("y")
	, xRange(), yRange()
	, legendPos("bottom right")
{
}

void Figure::SetLogX(bool _logx){
	logx = _logx;
}

void Figure::SetLogY(bool _logy){
	logy = _logy;
}
void Figure::SetOutputName(std::string name){
	outputName = name;
}
void Figure::SetXLabel(std::string _xLabel){
	xLabel = _xLabel;
}
void Figure::SetYLabel(std::string _yLabel){
	yLabel = _yLabel;
}
void Figure::SetXUpper(double xUpper){
	xRange.SetUpper(xUpper);
}
void Figure::SetXLower(double xLower){
	xRange.SetLower(xLower);
}
void Figure::SetYUpper(double yUpper){
	yRange.SetUpper(yUpper);
}
void Figure::SetYLower(double yLower){
	yRange.SetLower(yLower);
}

Curve* Figure::AddCurve(int xCol, int yCol){
	curves.push_back(new Curve(xCol, yCol));
	return (Curve*)curves.back();
}

string Figure::GetScript(){
	string res = "";
	res += "set terminal pdfcairo font \"Gill Sans,9\" linewidth 4 rounded fontscale 1.0\n";
	res += "set termoption dashed\n";
	res += "set style line 80 lt rgb \"#808080\"\n";
	res += "set style line 81 lt 0  # dashed\n";
	res += "set style line 81 lt rgb \"#808080\"  # grey\n";
	res += "set grid back linestyle 81\n";
	res += "set border 0x3 back linestyle 80\n";
	res += "set xtics nomirror\n";
	res += "set ytics nomirror\n";
	res += "\n";

	if (logx)
		res += "set log x\n";
	if (logy)
		res += "set log y\n";
	res += "set output \"" + outputName + "\"\n";
	res += "set xlabel \"" + xLabel + "\"\n";
	res += "set ylabel \"" + yLabel + "\"\n";
	res += "set xrange "+ xRange.GetScript() + "\n";
	res += "set yrange "+ yRange.GetScript() + "\n";
	res += "set key " + legendPos + "\n";
	res += "\n";
	res += "plot \\\n";
	for (int i = 0; i < curves.size(); i++){
		res += curves[i]->GetScript();
		if (i + 1 < curves.size())
			res += ",\\\n";
		else 
			res += "\n";
	}
	return res;
}

void Figure::Plot(string scriptName){
	ofstream fout;
	if (scriptName == ""){
		scriptName = "figure_cpp.gp";
		fout.open(scriptName);
		fout << GetScript() << endl;
		fout.close();
		system(("gnuplot " + scriptName).c_str());
		remove(scriptName.c_str());
	}else {
		fout.open(scriptName);
		fout << GetScript() << endl;
		fout.close();
		system(("gnuplot " + scriptName).c_str());
	}
}
} /* namespace plot */
} /* namespace bright_lib */
