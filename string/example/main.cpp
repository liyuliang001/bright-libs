#include <bright_lib/string/string.hpp>

using namespace std;
using namespace bright_lib;

int main(){
	string s="1 \n23  456 \t7890";
	auto res = split(s, " \t\n");
	for (auto &tok : res)
		printf("%s\n", tok.c_str());
}
