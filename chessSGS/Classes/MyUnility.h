#pragma once
#include <string>

class MyUnility
{
public:
	MyUnility();
	~MyUnility();

	static std::string gbk_2_utf8(const std::string text);
};