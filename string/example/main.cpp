#include <bright_lib/string/string.hpp>

using namespace std;
using namespace bright_lib;

int main(){
	string s="  1 \n23  456 \t7890\n";
	auto res = split(trim_copy(s));
	for (auto &tok : res)
		printf("%s\n", tok.c_str());
}
