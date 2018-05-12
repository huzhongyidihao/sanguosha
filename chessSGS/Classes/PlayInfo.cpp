#include "PlayInfo.h"

PlayInfo::PlayInfo() :_playerName("huzhongyi"), owner(0), _playeridentity(0), _playerRole("skongming"), _roleHealth(4), _roleSex(0), _rolePokerUpper(4), _roleCurrHealth(_roleHealth),
AttackRange(1), UsableShaPokerCounts(1), UsableTaoPoker(0), UsableWinebuffer(0)
{


}
PlayInfo::PlayInfo(int owner):PlayInfo()
{
	if (owner==1)
	{
		_playerName = "Robot001";
		_playeridentity = 1;
			_roleHealth=4;
			_roleCurrHealth = 4;
		_playerRole = "hetaihou";
		_roleSex = 1;
	}
	
}

//PlayInfo::PlayInfo(const PlayInfo &obj):_playerName(obj._playerName),
//owner(obj.owner),_playeridentity(obj._playeridentity),_playerRole(obj._playerRole),
//_rolePokerUpper(obj._rolePokerUpper)
//{
//
//	_playPokerSlot.assign(obj._playPokerSlot.begin(), obj._playPokerSlot.end());
//	_roleSkill.assign(obj._roleSkill.begin(), obj._roleSkill.end());
//	buffstate.assign(obj.buffstate.begin(), obj.buffstate.end());
//
//
//}

//PlayInfo & PlayInfo::operator=(const PlayInfo &obj) 
//{
//	_playerName=obj._playerName;
//	owner = obj.owner;
//	_playeridentity=obj._playeridentity;
//	_playerRole=obj._playerRole;
//	_rolePokerUpper=obj._rolePokerUpper;
//	_roleSkill=obj._roleSkill;
//	buffstate=obj.buffstate;
//	auto it1 = obj._playPokerSlot.begin();
//	auto it2 = obj._playPokerSlot.end();
//	_playPokerSlot.assign(it1, it2);
//	return *this;
//	
//}

PlayInfo::~PlayInfo()
{
	
}


void PlayInfo::SetPlaySkill()
{
	_roleSkill.push_back("Skill01");
}

void PlayInfo::losePlayHealth()
{
	_roleCurrHealth--;
}

void PlayInfo::recovePlayHealth()
{
	if (_roleCurrHealth<_roleHealth)
	{
		_roleCurrHealth++;
	/*	log("-----------currhealth=%d",_roleCurrHealth);
		log("-----------jia xue a !!!!!!!!--");*/
	}
	
	
}

int PlayInfo::GetPokerUpper()
{
	_rolePokerUpper = _roleCurrHealth;
	return _rolePokerUpper;
	
}

void PlayInfo::SetPlayState()
{
	_roleDeath = true;
}

bool  PlayInfo::SetPlayerIdentity()
{
	
	return true;
}