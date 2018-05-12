/*
扑克牌类

*/
#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Poker//:public cocos2d::Sprite
{
	
public:
	
	Poker(int );
	~Poker();
//	static Poker* Create(int index);
//	bool init();
	//Sprite* getSprite();
	void PokerPosition(float x, float y);
	cocos2d:: Sprite* pokerPic;//扑克牌精灵

	bool IsCanUse;//是否能够使用,如 满血 桃 就不能使用 标志为否
	bool IsSelect;//是否被选中
	bool IsTopPoker;//是否被上抬

	bool IsCanUsableCurr;//当前是否能够使用
	int pokerid;//每类卡牌唯一标识 目前桃0 杀1 闪2


private:
	int count;//扑克牌点数 1-13 
	int flowerColor;//花色1-4 黑红梅方
	
	int typeIndex;//类型索引  基本牌0 装备牌1 锦囊牌2 武将牌3 身份牌4
	
	std::string  name;//卡牌名称,可重复
	std::string descir;//卡牌说明


private:
	EventListenerTouchOneByOne* listener;
	EventDispatcher*eventdispatcher;//事件调度器
private:
	//辅助函数
	void CreateSpecificPoker(int);//创建特定的牌

	bool touchBegin(Touch*touch, Event*event);
	void touchMove(Touch*touch, Event*event);
	void touchEnd(Touch*touch, Event*event);
	void touchCancelled(Touch*touch, Event*event);
};

