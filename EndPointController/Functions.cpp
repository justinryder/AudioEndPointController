

#include "Functions.h"

#include <algorithm>

std::wstring string_to_wstring(const std::string& src)
{
	std:: wstring tmp;
	tmp.resize(src.size());
	std:: transform(src.begin(), src.end(), tmp.begin(), btowc);
	return tmp;
}

std::string wstring_to_string(const std::wstring& src)
{
	std:: string tmp;
	tmp.resize(src.size());
	std:: transform(src.begin(), src.end(), tmp.begin(), wctob);
	return tmp;
}