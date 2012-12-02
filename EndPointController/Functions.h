

#pragma once

#include <string>

// Converts a string to a wstring
std::wstring string_to_wstring(const std::string& src);

// Converts a wstring to a string
std::string wstring_to_string(const std::wstring& src);

void printHelp();