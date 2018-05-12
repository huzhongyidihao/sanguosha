/*
玩家信息类,存储所有玩家信息提供给GameUI显示,以及游戏逻辑类交互.
*/
#pragma once
#include <string>
#include <vector>
#include "Poker.h"
class PlayInfo
{


public:
	PlayInfo();
	PlayInfo(int owner);
	//PlayInfo(const PlayInfo&);
	//PlayInfo& operator=(const PlayInfo&);
	~PlayInfo();

public:
	//设置玩家身份
	bool SetPlayerIdentity();

	void SetPlaySkill();

	void losePlayHealth();//失去一点生命
	void recovePlayHealth();//恢复一点生命


	int GetPlayerIdentity() //获取玩家身份
	{
		return _playeridentity;
	}
	int GetPlayerHealth()
	{
		return _roleCurrHealth;
	}
	int GetPlayMaxHealth()
	{
		return _roleHealth;
	}
	int GetRoleSex()//获取角色性别
	{
		return _roleSex;
	}
	int GetPokerUpper();//返回角色手牌上限
	
	void SetPlayState();//修改玩家状态,主要用来修改生死


	std::vector<int> _playPokerSlot;//玩家手牌槽

	/*玩家用牌状况标记*/
	int UsableShaPokerCounts;//能够使用的杀的张数
	bool UsableWinebuffer;//是否得到过酒buffer,杀伤害加一的buffer
	bool UsableAttackOther;//能够攻击其他玩家
	bool UsableTaoPoker;//能否使用桃牌
	/*玩家游戏状态标记*/
	int AttackRange;//攻击距离

	
	/*  */
	
private:
	std::string _playerName;//玩家昵称
	int owner;//控制者,0代表玩家 1代表电脑
	int _playeridentity;//玩家身份 ---通过身份牌获取
	int _rolePokerUpper;//手牌上限
	std::string _playerRole;//玩家角色  ----通过武将牌获取
	int _roleHealth;//角色生命值
	int _roleCurrHealth;//当前生命值
	bool _roleDeath;//玩家死亡
	int _roleSex;//角色性别
	std::vector<std::string> _roleSkill;//角色技能组



	

	/*高级属性*/
	//int* equip;//装备栏,0代表无装备,包括武器、防具、防御马、进攻马，共四个元素
	std::vector<int> buffstate;//buffer状态: 酒,裸衣

};
