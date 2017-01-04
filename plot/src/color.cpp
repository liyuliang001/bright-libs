#include "color.hpp"

using namespace std;

namespace bright_lib{
namespace plot{

Color::Color()
	: type(Num), number(0), rgb("black")
{
}

string Color::GetScript(){
	switch (type){
		case Num:
			return "lc " + to_string(number);
		case Rgb:
			return "lc rgb \"" + rgb + "\"";
	}
}

void Color::SetNum(int _number){
	type = Num;
	number = _number;
}

void Color::SetRgb(string _rgb){
	type = Rgb;
	rgb = _rgb;
}

void Color::Set(int _number){
	SetNum(_number);
}

void Color::Set(std::string _rgb){
	SetRgb(_rgb);
}

} /* namespace plot */
} /* namespace bright_lib */
