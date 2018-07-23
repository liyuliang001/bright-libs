#include <vector>
#include <bright_lib/random/rand.hpp>

using namespace std;
using namespace bright_lib::random;

int main(){
	vector<Distribution<double>*> d;
	d.push_back(new NormalDistribution<double>(-5, 2));
	d.push_back(new ExponentialDistribution<double>(0.1));
	d.push_back(new UniformRealDistribution<double>(0, 100));
	d.push_back(new CustomDistribution<double>("cdf.txt"));
	for (auto p : d){
		printf("%lf\n", (*p)());
	}
}
