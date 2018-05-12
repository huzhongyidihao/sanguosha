/*
游戏主循环
单例类
*/
#pragma once
#include "PlayInfo.h"


class GameLoop
{
	
public:

	static GameLoop* GetInstance()//获取游戏主循环唯一的实例  _gamejudge
	{
		static GameLoop* _gamejudge;
		return _gamejudge;
	}

	/*--------创建玩家信息---*/


	void addPlayer(PlayInfo*,int);


	/*-------更新玩家信息   --------*/
	
	void setPlayPokerSlot(PlayInfo*,int type);//修改指定玩家playIndex 的手牌,type 表示操作类型 
	void setPlayPokerState(PlayInfo*);//修改指定玩家的回合状态: 包括 准备、判定、摸牌、出牌、弃牌已经阵亡
	void setPlayHealth(PlayInfo*, int vaule);//修改生命值
	void setPlayEquip(PlayInfo*, int equipIndex);//修改装备栏
	void setPlaySkill(PlayInfo*, std::string Oldskill,std::string Newskill);//修改技能
	void setPlayBuffer(PlayInfo*, int bufferstate);//修改buff状态

	/* 获取玩家信息容器 */
//	PlayInfo* getPlayInfo(int index);


private:
	static GameLoop* _gamejudge;

	GameLoop() {};
	GameLoop(const GameLoop&);
	GameLoop& operator=(const GameLoop&);

	class autoDelet
	{
		~autoDelet()
		{
			if (_gamejudge)
			{
				delete _gamejudge;
			}
		}
	};
	static autoDelet obj;
};