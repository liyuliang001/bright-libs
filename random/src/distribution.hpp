#ifndef _BRIGHT_LIB__RANDOM__DISTRIBUTION_HPP
#define _BRIGHT_LIB__RANDOM__DISTRIBUTION_HPP

#include <random>
#include <ctime>
#include "custom_rand.hpp"

namespace bright_lib{
namespace random{

template<typename RetType>
class Distribution{
public:
	std::default_random_engine generator;

	Distribution(){
		timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		generator.seed(ts.tv_nsec);
	}
	virtual RetType operator()() = 0;
};

template<typename RetType = double>
class NormalDistribution : public Distribution<RetType>{
public:
	std::normal_distribution<RetType> distr;
	NormalDistribution(RetType mean = 0.0, RetType std = 1.0) : distr(mean, std) {}
	RetType operator()(){
		return distr(this->generator);
	}
};

template<typename RetType = double>
class ExponentialDistribution : public Distribution<RetType>{
public:
	std::exponential_distribution<RetType> distr;
	ExponentialDistribution(RetType lambda = 1.0) : distr(lambda){}
	RetType operator()(){
		return distr(this->generator);
	}
};

template<typename RetType = double>
class UniformRealDistribution : public Distribution<RetType>{
public:
	std::uniform_real_distribution<RetType> distr;
	UniformRealDistribution(RetType a = 0.0, RetType b = 1.0) : distr(a, b){}
	RetType operator()(){
		return distr(this->generator);
	}
};

template<typename RetType = double>
class CustomDistribution : public Distribution<RetType>{
public:
	CustomRand<RetType> distr;
	CustomDistribution(){}
	CustomDistribution(Cdf _cdf) : distr(_cdf){}
	RetType operator()(){
		return distr(this->generator);
	}
};

} /* namespace random */
} /* namespace bright_lib */

#endif /* _BRIGHT_LIB__RANDOM__DISTRIBUTION_HPP */
