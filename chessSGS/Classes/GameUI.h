#pragma once
/*
主游戏界面UI

*/

#include "cocos2d.h"
#include "ui/CocosGUI.h"


USING_NS_CC;
class PlayInfo;
class Poker;
typedef enum 
{
	thandPoker_Tag  //手牌
	,tgiveupPoker_Tag //弃牌堆的牌
	,tSkill_Tag //技能
	,tEquip_Tag //装备


}SpriteTags;
class GameUI:public cocos2d::Layer
{
	//friend class GameScene;
public:
	bool init();

	virtual void onEnter();
	virtual void onExit();

	void menuReOpen(Ref*pSender);//重开
	void menuExit(Ref*pSender);//退出游戏
	void menuaddpoker(Ref*pSender);
	void menuusepoker(Ref*pSender);
	void menugiveuppoker(Ref*pSender);
	//用牌交互
	void menuOkPoker(Ref*pSender);//确定
	void menuCancelPoker(Ref*pSender);//取消

	void update(float delta);
	/* 玩家摸牌 显示 */
	void addPoker( int ,int);
	/* 玩家使用牌(包括回合内外) 显示 */
	void usePoker(int num=1);
	/* 玩家弃牌 显示 */
	void giveupPoker( );
	/* 电脑玩家弃牌 显示*/
	void giveupPoke_Robot(int );
	void fun1(Ref*);
	/*弃牌堆的更新*/
	void Updategiveupheap();

	CREATE_FUNC(GameUI);

	//初始化角色信息
	void initRoleInfo(PlayInfo* player);
	//更新角色信息(显示)
	void UpdateRoleInfo(PlayInfo*player);

	//初始化对手信息
	void initFoeInfo(PlayInfo* player);
	//更新对手信息(显示)
	void UpdatFoeInfo(PlayInfo*player);

	Color3B color;
	Label*CurrenState;
	MenuItemImage* menuButtonOK;//确认
	MenuItemImage* menuButtonCancel;//取消
	Menu*buttonmenu;//确认/取消 管理菜单

	int SelectPokerCounts;//可选中牌的上限  默认为1,即一次出一张牌，除非技能等因素影响这个参数
	
	bool isAddPoker;
	bool isUsePoker;//是否点击了确定按钮来出牌
	void CountDown(float dt=5.0f,int index=0);//倒计时函数实现延时功能
	void setTimeBarwithtime(float );
	void setTimeBarwithtimeIngiveup(float);
	bool isCountDown;//是否在读条 即调用了CountDown 
	bool isEndUsePokeState;//是否结束出牌阶段

	bool isUpdateGiveupHeap;//是否更新弃牌堆,释放所有的内存

	void SwapTimeBar();//交换当前回合的时间读条指针,令当前回合进行读条的Loadingbar 指针指向play的时间读条指针
	
	void UpdateShowPokerSlot(PlayInfo*);//更新手牌槽,外部调用
	void DrawShowPokerSlot();//绘制手牌槽的牌
	void addgiveupheap(Poker*);//添加牌到弃牌堆



	void TopPoler(Poker*);//顶出选中的牌,将其在手牌中向上抬 显示已选中
	void DownPoker(Poker*);//收回上抬显示的牌,使其回归原位

	void DrawnDarkAllPoker();//将所有牌描绘颜色变暗

	void AdjustPoker();//手牌调整:更新手牌位置,排序

	std::vector<Poker*>showpokerslot;//玩家需要显示的手牌槽
	bool isSortPokers;//是否排序手牌

	std::deque<Poker*>giveupPokerHeap;//弃牌堆
	bool isEndGiveUpPokeState;//是否结束了弃牌阶段
	/*玩家出牌操作处理相关*/
	bool isSelectShaPoker;//是否选择了杀

	bool isExtraUsePoker;//是否属于额外用牌阶段
	bool FoeIsUsePoker;//电脑是否用牌
	Label*_showFoePokerNums;
	ui::LoadingBar* timebar;
	ui::LoadingBar* timebarRobot;
private:
	//std::deque<Poker*>SelectPokers;//选中牌的集合
	std::vector<int>showIntslot;
	
	Sprite*bg;//背景图片
	Sprite*equipment;//装备栏图片
	Sprite*pokerSlot;//手牌槽背景图片
	Sprite*rolePicInfo;//角色ui图片信息
	//Vector<Sprite*>roleHealthInfo;

	Sprite*foeInfoShow;
	

	

	Label* timelabel;
	
	Label*_showOurPokerNums;

	
	int _lastpokerpoint;//手牌槽最后一张牌的位置
	int _lastheappoint;//弃牌堆首张牌的位置

	EventDispatcher*eventdispatcher;

	bool onTouchBegan(Touch*touch, Event*event); 
	void onTouchMoved(Touch*touch, Event*event);
	void onTouchEnded(Touch*touch, Event*event);
	void onTouchCancelled(Touch*touch, Event*event);


	void isSelectPoker();//判断是否选中牌
};

