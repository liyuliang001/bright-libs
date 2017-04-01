#include <cstdio>
#include <iostream>
#include <bright_lib/types/bigint.hpp>

using namespace bright_lib::types;
using namespace std;

int main(){
	BigInt<128> i, j, k;
	BigInt<640> x;
	for (int i = 0; i < 10; i++)
		x.d[i] = 0xfedcba9876543210;
	i.d[0] = 0xfedcba9876543210; j.d[0] = 0xfedcba9876543210; k.d[0] = 0xfedcba9876543210;
	i.d[1] = 0xfedcba9876543210; j.d[1] = 0xfedcba9876543210; k.d[1] = 0xfedcba9876543210;
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
}
