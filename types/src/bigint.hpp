#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <stdint.h>
#include <cstring>

namespace bright_lib{
namespace types{

#define N_U64 ((nbit-1)/64+1)
template <uint32_t nbit>
class BigInt{
public:
	uint64_t d[N_U64];

	BigInt(){
		memset(d, 0, sizeof(d));
	}
	int cmp(const BigInt<nbit> &b)const {
		for (int i = N_U64-1; i >= 0; i--){
			if (d[i] < b.d[i])
				return -1;
			if (d[i] > b.d[i])
				return 1;
		}
		return 0;
	}

	BigInt& operator=(uint64_t b){
		memset(d, 0, sizeof(d));
		d[0] = b;
		return *this;
	}
	bool operator==(const BigInt<nbit> &b)const {return cmp(b) == 0;}
	bool operator<(const BigInt<nbit> &b)const {return cmp(b) == -1;}
	bool operator<=(const BigInt<nbit> &b)const {return cmp(b) <= 0;}
	bool operator>(const BigInt<nbit> &b)const {return cmp(b) == 1;}
	bool operator>=(const BigInt<nbit> &b)const {return cmp(b) >= 0;}
	BigInt operator<<(int s) const {
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

	BigInt operator>>(int s)const {
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

	BigInt operator|(uint64_t s)const {
		BigInt res(*this);
		res.d[0] |= s;
		return res;
	}
	BigInt& operator|=(uint64_t s){
		d[0] |= s;
		return *this;
	}

	BigInt operator&(uint64_t s)const {
		BigInt res(*this);
		res.d[0] &= s;
		return res;
	}
	BigInt& operator&=(uint64_t s){
		d[0] &= s;
		return *this;
	}

	BigInt operator^(uint64_t s)const {
		BigInt res(*this);
		res.d[0] ^= s;
		return res;
	}
	BigInt& operator^=(uint64_t s){
		d[0] ^= s;
		return *this;
	}

	std::string hex()const {
		std::string res(nbit / 4, 0);
		for (int i = 0; i < N_U64; i++)
			sprintf(&res[i*16], "%016lx", d[N_U64 - 1 - i]);
		return res;
	}
};

} /* namespace types */
} /* namespace bright_lib */

namespace std{
	template<uint32_t nbit>
	class hash<bright_lib::types::BigInt<nbit> >{
		public:
		std::size_t operator()(const bright_lib::types::BigInt<nbit> &b) const {
			const uint8_t *key = (const uint8_t*)b.d;
			size_t len = N_U64 * 8;
			uint32_t seed = 0;

			uint32_t h = seed;
			if (len > 3) {
				const uint32_t* key_x4 = (const uint32_t*) key;
				size_t i = len >> 2;
				do {
					uint32_t k = *key_x4++;
					k *= 0xcc9e2d51;
					k = (k << 15) | (k >> 17);
					k *= 0x1b873593;
					h ^= k;
					h = (h << 13) | (h >> 19);
					h += (h << 2) + 0xe6546b64;
				} while (--i);
				key = (const uint8_t*) key_x4;
			}
			if (len & 3) {
				size_t i = len & 3;
				uint32_t k = 0;
				key = &key[i - 1];
				do {
					k <<= 8;
					k |= *key--;
				} while (--i);
				k *= 0xcc9e2d51;
				k = (k << 15) | (k >> 17);
				k *= 0x1b873593;
				h ^= k;
			}
			h ^= len;
			h ^= h >> 16;
			h *= 0x85ebca6b;
			h ^= h >> 13;
			h *= 0xc2b2ae35;
			h ^= h >> 16;
			return h;
		}
	};
}
#undef N_U64

#endif /* BIGINT_HPP */
