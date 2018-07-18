#ifndef _BRIGHT_LIB__RAND__CUSTOM_RAND_HPP
#define _BRIGHT_LIB__RAND__CUSTOM_RAND_HPP

#include <vector>
#include <cassert>
#include "rand_double.hpp"

namespace bright_lib{
namespace rand{

class Cdf{
public:
	struct Point{
		double x, y;
		Point() : x(0), y(0) {}
		Point(double _x, double _y) : x(_x), y(_y) {}
	};
	std::vector<Point> p;

	void add(double x, double y){ p.emplace_back(x, y);}
	bool test(){
		if (p.size() < 2)
			return false;
		if (p[0].y != 0)
			return false;
		if (p.back().y != 100)
			return false;
		for (int i = 1; i < p.size(); i++)
			if (p[i-1].x >= p[i].x || p[i-1].y >= p[i].y)
				return false;
		return true;
	}
	double get_avg(){
		double s = 0;
		for (int i = 1; i < p.size(); i++)
			s += (p[i].x + p[i-1].x) * (p[i].y - p[i-1].y) / 2;
		return s / 100;
	}
	double get_max(){
		return p.back().x;
	}
	double get_min(){
		return p[0].x;
	}
};

class CustomRand{
public:
	Cdf cdf;

	bool test_cdf(){ return cdf.test();}
	double rand(){
		double r = rand_double() * 100;
		for (int i = 1; i < cdf.p.size(); i++){
			if (r <= cdf.p[i].y)
				return cdf.p[i-1].x + (cdf.p[i].x - cdf.p[i-1].x) / (cdf.p[i].y - cdf.p[i-1].y) * (r - cdf.p[i-1].y);
		}
		assert(0);
	}
};

} /* namespace rand */
} /* namespace bright_lib */

#endif /* _BRIGHT_LIB__RAND__CUSTOM_RAND_HPP */
