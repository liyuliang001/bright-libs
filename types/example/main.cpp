#include <cstdio>
#include <iostream>
#include <bright_lib/types/bigint.hpp>
#include <unordered_map>
#include <map>
#include <vector>
#include <ctime>

using namespace bright_lib::types;
using namespace std;

double operator-(const timespec &a, const timespec &b){
	return (a.tv_sec - b.tv_sec) + (a.tv_nsec - b.tv_nsec) * 1e-9;
}

int main(){
	BigInt<128> i, j, k;
	BigInt<640> x;
	for (int i = 0; i < 10; i++)
		x.d[i] = 0xfedcba9876543210;
	i.d[0] = 0xfedcba9876543210; j.d[0] = 0xfedcba9876543210; k.d[0] = 0xfedcba9876543210;
	i.d[1] = 0xfedcba9876543210; j.d[1] = 0xfedcba9876543210; k.d[1] = 0xfedcba9876543210;
	printf("%d\n", i==j);
	printf("%d\n", i<=j);
	printf("%d\n", i<j);
	printf("%d\n", i>=j);
	printf("%d\n", i>j);
	printf("%d\n", i<=k);
	printf("%d\n", i<k);
	printf("%d\n", i>=k);
	printf("%d\n", i>k);
	cout<<i.hex()<<endl << j.hex() << endl << k.hex() << endl;
	k<<=4;
	i<<=8;
	j<<=68;
	cout<<i.hex()<<endl << j.hex() << endl << k.hex() << endl;
	k>>=4;
	i>>=8;
	j>>=68;
	cout<<i.hex()<<endl << j.hex() << endl << k.hex() << endl;
	cout<<x.hex()<<endl;
	x<<=1;
	x>>=1;
	cout<<x.hex()<<endl;
	x>>=12;
	x<<=12;
	cout<<x.hex()<<endl;
	x<<=16;
	x>>=16;
	cout<<x.hex()<<endl;
	x>>=136;
	x<<=136;
	cout<<x.hex()<<endl;
	x<<=132;
	cout<<x.hex()<<endl;
	x>>=132;
	cout<<x.hex()<<endl;
	x |= 0x00012300;
	cout<<x.hex()<<endl;
	x &= 0x0000fff0;
	cout<<x.hex()<<endl;

	// test map performance
#define TEST_NBIT 128
	int n_key = 1000000;
	vector<uint64_t> k1(n_key);
	vector<BigInt<TEST_NBIT> > k2(n_key);
	for (int i = 0; i < n_key; i++){
		k1[i] = i;
		k2[i].d[0] = i;
	}
	unordered_map<uint64_t, int> um1;
	unordered_map<BigInt<TEST_NBIT>, int> um2;
	map<uint64_t, int> m1;
	map<BigInt<TEST_NBIT>, int> m2;
	timespec t0, t1, t2;
	clock_gettime(CLOCK_MONOTONIC, &t0);
	for (int i = 0; i < k1.size(); i++)
		um1[k1[i]] = i;
	clock_gettime(CLOCK_MONOTONIC, &t1);
	for (int i = 0; i < k2.size(); i++)
		um2[k2[i]] = i;
	clock_gettime(CLOCK_MONOTONIC, &t2);
#if 0
	for (auto it = um2.begin(); it != um2.end(); it++)
		cout<< it->first.hex() << ' ' << it->second << endl;
#endif
	printf("%.9lf %.9lf\n", t1-t0, t2-t1);

	unordered_map<BigInt<128>, int> m;
	m[i] = 1;
	m[j] = 2;
	m[k] = 3;
	for (auto it = m.begin(); it != m.end(); it++)
		cout<< it->first.hex() << ' '<< it->second << endl;
}
