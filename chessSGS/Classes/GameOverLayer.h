/*
游戏结束后显示在最上层的 操作layer
*/
#pragma once
#include "cocos2d.h"

class GameOverLayer :public cocos2d::LayerColor
{

public:
	bool init();
	void onEnter();
	void onExit();
	void update(float delta);

	CREATE_FUNC(GameOverLayer);

	void menuRepPlay(Ref*pSender);
	void menuExit(Ref* pSender);

private:
	

};