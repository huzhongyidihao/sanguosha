/*
≥£¡ø¿‡
*/
#pragma once
#include "cocos2d.h"
class Constant
{
public:
	static Constant* GetInstance()
	{
		static Constant* _instance;
		return _instance;
	}
	static void InitData();
private:
	static cocos2d::ValueMap pokerdetail;

private:
	Constant() {};
	Constant(const Constant&);
	Constant& operator=(const Constant&);

};

