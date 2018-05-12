#include "GameLoop.h"
#include <exception>
USING_NS_CC;


void  GameLoop::setPlayPokerSlot(PlayInfo*player,int type)
{

	
}

void GameLoop::setPlayPokerState(PlayInfo*player)
{
	log("\n----------setPlayPokerState-----------\n");
}

void GameLoop::setPlayHealth(PlayInfo*player, int vaule)
{
	log("\n----------setPlayHealth-----------\n");
	
}

void GameLoop::setPlayEquip(PlayInfo*player, int equipIndex)
{
	log("\n----------setPlayEquip-----------\n");
}

void GameLoop::setPlaySkill(PlayInfo*player, std::string Oldskill, std::string Newskill)
{
	log("\n----------setPlaySkill-----------\n");
}

void GameLoop::setPlayBuffer(PlayInfo*player, int bufferstate)
{
	log("\n----------setPlayBuffer-----------\n");
}
//PlayInfo* GameLoop::getPlayInfo(int index)
//{
//	log("----\n---read ERROR!-----\n");
//	//auto playinfo = *(_playCollection.begin());
//	auto playinfo = _playCollection[index];
//	if (playinfo)
//	{
//		log("\n-----------------\n--------playinfo have read!--------\n-----------");
//	}
//	else
//	{
//		log("\n-----------------\n--------playinfo is nullptr!--------\n-----------");
//	}
//	
//	return playinfo;
//}

void GameLoop::addPlayer(PlayInfo*obj,int index)
{
	
	
}

