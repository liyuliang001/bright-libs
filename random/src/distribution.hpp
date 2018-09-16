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
	virtual RetType get_mean() = 0;
};

template<typename RetType = double>
class NormalDistribution : public Distribution<RetType>{
public:
	RetType mean, std;
	std::normal_distribution<RetType> distr;

	NormalDistribution(RetType _mean = 0.0, RetType _std = 1.0) : mean(_mean), std(_std), distr(_mean, _std) {}
	RetType operator()(){ return distr(this->generator);}
	RetType get_mean(){ return mean;}
};

template<typename RetType = double>
class ExponentialDistribution : public Distribution<RetType>{
public:
	RetType lambda;
	std::exponential_distribution<RetType> distr;

	ExponentialDistribution(RetType _lambda = 1.0) : lambda(_lambda), distr(_lambda){}
	RetType operator()(){ return distr(this->generator);}
	RetType get_mean(){ return 1.0 / lambda;}
};

template<typename RetType = double>
class UniformRealDistribution : public Distribution<RetType>{
public:
	RetType a, b;
	std::uniform_real_distribution<RetType> distr;

	UniformRealDistribution(RetType _a = 0.0, RetType _b = 1.0) : a(_a), b(_b), distr(_a, _b){}
	RetType operator()(){ return distr(this->generator);}
	RetType get_mean(){ return (a + b) / 2;}
};

template<typename RetType = double>
class CustomDistribution : public Distribution<RetType>{
public:
	CustomRand<RetType> distr;

	CustomDistribution(){}
	CustomDistribution(const std::string &cdf_filename) : distr(cdf_filename) {}
	CustomDistribution(Cdf _cdf) : distr(_cdf){}
	RetType operator()(){ return distr(this->generator);}
	RetType get_mean(){ return distr.cdf.get_avg();}
};

} /* namespace random */
} /* namespace bright_lib */

#endif /* _BRIGHT_LIB__RANDOM__DISTRIBUTION_HPP */
