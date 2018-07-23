#ifndef _BRIGHT_LIB__STRING__STRING_HPP
#define _BRIGHT_LIB__STRING__STRING_HPP

#include <string>
#include <vector>
#include <locale>
#include <algorithm>
#include <cstring>

namespace bright_lib{

static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
				return !std::isspace(ch);
				}));
}

static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
				return !std::isspace(ch);
				}).base(), s.end());
}

static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

static inline std::vector<std::string> split(std::string &s, const char *delim){
	std::vector<std::string> res;
	char* saveptr;
	char* str = &s[0];
	for (char* tok = strtok_r(str, delim, &saveptr); tok; tok = strtok_r(NULL, delim, &saveptr)){
		res.push_back(tok);
	}
	return res;
}

}

#endif /* _BRIGHT_LIB__STRING__STRING_HPP */
