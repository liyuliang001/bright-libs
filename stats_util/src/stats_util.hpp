#ifndef BRIGHT_LIB__STATS_UTIL_HPP
#define BRIGHT_LIB__STATS_UTIL_HPP
#include <vector>
#include <cmath>

namespace bright_lib{
namespace stats_util{

template <class T>
double GetPercentile(const std::vector<T> &v, double pct){
	if (v.size() == 0)
		return 0;
	double p = pct * (v.size() - 1);
	int l = floor(p), u = ceil(p);
	double f = (p - l);
	return (1 - f) * v[l] + f * v[u];
}

template <class T>
double GetMean(const std::vector<T> &v){
	double sum = 0;
	for (int i = 0; i < (int)v.size(); i++)
		sum += v[i];
	return sum / v.size();
}

template <class T>
double GetVar(const std::vector<T> &v){
	double mean = GetMean(v);
	double sum = 0;
	for (int i = 0; i < (int)v.size(); i++){
		double d = v[i] - mean;
		sum += d * d;
	}
	return sum / v.size();
}

template <class T>
double GetStd(const std::vector<T> &v){
	double var = GetVar(v);
	return sqrt(var);
}

} /* namespace stats_util */
} /* namespace bright_lib */

#endif /* BRIGHT_LIB__STATS_UTIL_HPP */
