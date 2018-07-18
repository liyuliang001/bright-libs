#include <cstdio>
#include <algorithm>
#include <bright_lib/rand/rand.hpp>

using namespace std;
using namespace bright_lib::rand;

int main(){
	CustomRand r;
	r.cdf.add(0.0,0.0);
	r.cdf.add(6, 50.0);
	r.cdf.add(8, 100.0);
	if (!r.test_cdf()){
		printf("invalid cdf\n");
		return -1;
	}
	printf("avg: %lf\n", r.cdf.get_avg());
	vector<double> x;
	for (int i = 0; i < 100; i++)
		x.push_back(r.rand());
	sort(x.begin(), x.end());
	for (int i = 0; i < 100; i++){
		printf("%lf ", x[i]);
		for (int j = 0; j < x[i] * 5; j ++)
			printf("*");
		printf("\n");
	}
}
