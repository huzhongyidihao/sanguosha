/*
游戏场景
*/
#pragma once
#include "cocos2d.h"
class GameUI;
class GameOverLayer;
class PlayInfo;
class Poker;
class GameScene:public cocos2d::Scene
{

public:
	bool init();
	CREATE_FUNC(GameScene);
	void update(float delta);

	~GameScene();



	void UpdatePlayState();//更新所有玩家的状态,判断游戏进程,主要用来鉴别是否死亡


	void SignUsablePoker();//标记能用的牌
private:
	void rifflePoker();//重新洗牌,创建一副新牌堆
	void UpdateCurrentPlayer();//更新当前玩家
	void GameOver();
	int GetOutPokerFromHeap();//从牌堆抽出牌
	int CurrentplayAddPoker(int);//当前玩家添加手牌
	void CurrentplayGiveupPoker(int);//当前玩家丢弃手牌
	//void Delay();

	/* 用牌方法判断 */
	void UsePoker();//根据选中的牌执行不同的方法
	
	void UseAnPokerThenUp(Poker*,int);//使用一张牌后放入弃牌堆
	void CreateOverLayer();


	GameUI* _mainLayer;
	GameOverLayer* _overLayer;

	
	std::vector<int> _pokerHeap;
	std::vector<PlayInfo*>_playerCollection;

	int count;//刷新一帧计数加一，到20*60=1200帧 则自动调用UpdateCurrentPlayer函数
    bool IsGameOver;//游戏是否结束
	int currentPlayer;//当前回合玩家
	bool IsOverState;//阶段是否结束
	int PlayState;//当前玩家游戏状态,包括: 0准备、1判定、2摸牌、3出牌、4弃牌 5已经阵亡

	

	/*牌效果*/
	void UseTaoPoker(Poker*,int);//桃
	void UseShaPoker(Poker*,int);//杀
	void UseShanPoker(Poker*,int);//决斗
	
	void PokerEffect(int);//卡牌特效

	void extraUsePoker(int target);//额外的出牌回合:回合外相应的"出牌阶段"
	int feedbackType;//响应类型,响应杀-决斗 南蛮 借刀 响应闪-杀 万剑  等等，暂时只能响应闪 0
	bool isOverFeedback;//是否完成响应
	void FoeUsePoker(int);//电脑的出牌选择

	
	float barprect;//电脑时间轴当前进度
};

