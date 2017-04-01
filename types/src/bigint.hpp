#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <stdint.h>
#include <cstring>

namespace bright_lib{
namespace types{

template <uint32_t nbit>
class BigInt{
public:
#define N_U64 ((nbit-1)/64+1)
	uint64_t d[N_U64];

	bool operator==(BigInt<nbit> &b){
		for (int i = 0; i < N_U64; i++)
			if (d[i] != b.d[i])
				return false;
		return true;
	}

	int cmp(BigInt<nbit> &b){
		for (int i = N_U64-1; i >= 0; i--){
			if (d[i] < b.d[i])
				return -1;
			if (d[i] > b.d[i])
				return 1;
		}
		return 0;
	}

	bool operator<(BigInt<nbit> &b){return cmp(b) == -1;}
	bool operator<=(BigInt<nbit> &b){return cmp(b) <= 0;}
	bool operator>(BigInt<nbit> &b){return cmp(b) == 1;}
	bool operator>=(BigInt<nbit> &b){return cmp(b) >= 0;}
	BigInt operator<<(int s){
		BigInt res;
		if (s > nbit){
			memset(res.d, 0, sizeof(res.d));
			return res;
		}
		int s64 = s / 64;
		for (int i = N_U64 - 1; i >= s64; i--)
			res.d[i] = d[i - s64];
		for (int i = s64 - 1; i >= 0; i--)
			res.d[i] = 0;

		s %= 64;
		for (int i = N_U64 - 1; i > 0; i--)
			res.d[i] = (res.d[i] << s) | (res.d[i-1] >> (64 - s));
		res.d[0] <<= s;
		return res;
	}
	BigInt& operator<<=(int s){return ((*this) = (*this) << s);}

	BigInt operator>>(int s){
		BigInt res;
		if (s > nbit){
			memset(res.d, 0, sizeof(res.d));
			return res;
		}
		int s64 = s / 64;
		for (int i = 0; i + s64 < N_U64; i++)
			res.d[i] = d[i + s64];
		for (int i = N_U64 - s64; i < N_U64; i++)
			res.d[i] = 0;

		s %= 64;
		for (int i = 0; i < N_U64 - 1; i++)
			res.d[i] = (res.d[i] >> s) | (res.d[i+1] << (64 - s));
		res.d[N_U64 - 1] >>= s;
		return res;
	}
	BigInt& operator>>=(int s){return ((*this) = (*this) >> s);}

	BigInt operator|(uint64_t s){
		BigInt res(*this);
		res.d[0] |= s;
		return res;
	}
	BigInt& operator|=(uint64_t s){
		d[0] |= s;
		return *this;
	}

	BigInt operator&(uint64_t s){
		BigInt res(*this);
		res.d[0] &= s;
		return res;
	}
	BigInt& operator&=(uint64_t s){
		d[0] &= s;
		return *this;
	}

	BigInt operator^(uint64_t s){
		BigInt res(*this);
		res.d[0] ^= s;
		return res;
	}
	BigInt& operator^=(uint64_t s){
		d[0] ^= s;
		return *this;
	}

	std::string hex(){
		std::string res(nbit / 4, 0);
		for (int i = 0; i < N_U64; i++)
			sprintf(&res[i*16], "%016lx", d[N_U64 - 1 - i]);
		return res;
	}
#undef N_U64
};

} /* namespace types */
} /* namespace bright_lib */

#endif /* BIGINT_HPP */
