#include "GameUI.h"
#include "Poker.h"
#include "PlayInfo.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"
#pragma execution_character_set("utf-8")
bool GameUI::init()
{
	if (!Layer::init())
	{
		return false;
	}
	log("\n----------------do init!--------------\n");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/*----------------初始化UI-----------------*/

	_lastpokerpoint = 150;
	_lastheappoint = 360;
	SelectPokerCounts = 1;
	//初始化背景
	bg = Sprite::create("pic/bg.png");
	bg->setAnchorPoint(Vec2::ZERO);
	bg->setPosition(Vec2::ZERO);
	//bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg,0);

	//初始化玩家手牌槽
	pokerSlot = Sprite::create("pic/pokerslot.png");
	pokerSlot->setAnchorPoint(Vec2::ZERO);
	pokerSlot->setPosition(200, 10);
	addChild(pokerSlot);
	//初始化用牌交互按钮
	menuButtonOK = MenuItemImage::create("pic/ok1.png", "pic/ok2.png","pic/ok3.png", CC_CALLBACK_1(GameUI::menuOkPoker, this));
	menuButtonOK->setScale(0.4);
	menuButtonCancel = MenuItemImage::create("pic/cancel1.png", "pic/cancel2.png", CC_CALLBACK_1(GameUI::menuCancelPoker, this));
	menuButtonCancel->setScale(0.4);
	buttonmenu = Menu::create(menuButtonOK, menuButtonCancel, nullptr);
	buttonmenu->setAnchorPoint(Vec2::ZERO);
	buttonmenu->setPosition(visibleSize.width - 320, 200);
	buttonmenu->alignItemsHorizontallyWithPadding(20);
	buttonmenu->setVisible(false);
	addChild(buttonmenu, 15);
	//初始 玩家化时间进度条
	timebar = ui::LoadingBar::create("pic/timebar.png");
	timebar->setDirection(ui::LoadingBar::Direction::LEFT);
	timebar->setAnchorPoint(Vec2::ZERO);
	timebar->setPercent(100.0);
	timebar->setPosition(Vec2(200, 160));
	timebar->setVisible(false);
	addChild(timebar);

	

	//初始化玩家装备槽
	auto weaponLabel = Label::createWithTTF("武器","fonts/DFPShaoNvW5-GB.ttf",18);
	auto armorLabel = Label::createWithTTF("防具", "fonts/DFPShaoNvW5-GB.ttf", 18);
	auto horse01Label = Label::createWithTTF("防御马", "fonts/DFPShaoNvW5-GB.ttf", 18);
	auto horse02Label = Label::createWithTTF("进攻马", "fonts/DFPShaoNvW5-GB.ttf", 18);
	weaponLabel->setAnchorPoint(Vec2::ZERO);
	armorLabel->setAnchorPoint(Vec2::ZERO);
	horse01Label->setAnchorPoint(Vec2::ZERO);
	horse02Label->setAnchorPoint(Vec2::ZERO);
	weaponLabel->setPosition(5, 65);
	armorLabel->setPosition(5, 45);
	horse01Label->setPosition(5, 25);
	horse02Label->setPosition(5, 5);
	addChild(weaponLabel);
	addChild(armorLabel);
	addChild(horse01Label);
	addChild(horse02Label);

	

	//初始化玩家角色信息
	rolePicInfo = Sprite::create("pic/rolehead.png");
	rolePicInfo->setAnchorPoint(Vec2::ZERO);
	rolePicInfo->setPosition(visibleSize.width-220, 80);
	addChild(rolePicInfo);

	/*初始化对手信息*/

	foeInfoShow = Sprite::create("pic/poker_wj_02.png",Rect(0,1,160,160));

	foeInfoShow->setPosition(Vec2(visibleSize.height - 210, visibleSize.width / 2));
	this->addChild(foeInfoShow, 0);
	
	//机器人回合进度条
	timebarRobot = ui::LoadingBar::create("pic/timerobot.png");
	timebarRobot->setDirection(ui::LoadingBar::Direction::LEFT);
	timebarRobot->setAnchorPoint(Vec2::ZERO);
	timebarRobot->setPercent(100.0);
	timebarRobot->setPosition(Vec2(2, -10));
	timebarRobot->setVisible(true);
	foeInfoShow->addChild(timebarRobot,5);





	/*系统设置*/
	MenuItemFont::setFontSize(20);
	MenuItemFont* menuExit = MenuItemFont::create("Exit", CC_CALLBACK_1(GameUI::menuExit,this));
	MenuItemFont*menuReOpen = MenuItemFont::create("ReOpent", CC_CALLBACK_1(GameUI::menuReOpen, this));

	/* 调试专用按钮*/
	MenuItemFont* menuAddPoker = MenuItemFont::create("AddPoker", CC_CALLBACK_1(GameUI::menuaddpoker, this));
	MenuItemFont*menuUsePoker = MenuItemFont::create("UsePoker", CC_CALLBACK_1(GameUI::menuusepoker,this));
	MenuItemFont*menuGiveUpPoker = MenuItemFont::create("GiveUpPoke", CC_CALLBACK_1(GameUI::menugiveuppoker,this));

	Menu* menu = Menu::create(menuReOpen, menuExit,menuAddPoker,menuUsePoker,menuGiveUpPoker, nullptr);
	menu->setAnchorPoint(Vec2(1, 1));
	menu->setPosition(60, visibleSize.height - 80);
	menu->alignItemsVerticallyWithPadding(10);
	addChild(menu, 1);

	CurrenState = Label::create("zhunbei", "Marker Felt", 32);
	CurrenState->setAnchorPoint(Vec2::ZERO);
	CurrenState->setPosition(120,220);
	addChild(CurrenState, 3);

	timelabel = Label::create("time", "Marker Felt", 16);
	timelabel->setAnchorPoint(Vec2::ZERO);
	timelabel->setPosition(70, 100);
	addChild(timelabel, 3);


	/*-------- 游戏相关 ---------*/
	isAddPoker = true;
	isUsePoker = false;
	isExtraUsePoker = false;
	isSelectShaPoker = false;
	FoeIsUsePoker=false;
	isEndUsePokeState = false;
	isEndGiveUpPokeState = false;
	scheduleUpdate();
	return true;
}
void GameUI::update(float delta)
{
	//if (SelectPokers.empty()!=true)//当有牌被选中时
	//{
	//	if (SelectPokers.size()>SelectPokerCounts)//是否大于上限
	//	{
	//		SelectPokers.pop_front();//删除最前面的元素
	//	}
	//}
	if (isExtraUsePoker)
	{
		if (timebar->getPercent()<0.001f)
		{
			isExtraUsePoker = false;
			timebar->setPercent(100.0f);
			timebar->setVisible(false);
			buttonmenu->setVisible(false);
			SwapTimeBar();
			timebar->setVisible(true);
			
			FoeIsUsePoker=true;
			log("----------FoeIsUsePoker=true---------------!");
		}
	}

}
void GameUI::onEnter()
{
	Layer::onEnter();
	log("\n----------------do onEnter!--------------\n");
	//SceneManager::GetInstance()->playBGM("music/Welcome To New York.mp3",true);	
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/Welcome To New York.mp3", true);

	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/汉风.mp3", true);

	/*触摸事件监听*/
	log("create listener");
	
	//setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	auto it=getTouchMode();
	if (it== Touch::DispatchMode::ONE_BY_ONE)
	{
		log("this touchmode is ONE_BY_ONE");
	}
	if (it==Touch::DispatchMode::ALL_AT_ONCE)
	{
		log("this touchmode is ALL_AT_ONCE");
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan=CC_CALLBACK_2(GameUI::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameUI::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameUI::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameUI::onTouchCancelled, this);
	eventdispatcher = Director::getInstance()->getEventDispatcher();
	eventdispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	log("add listener");
	log("do play music!");
}
void GameUI::onExit()
{
	Layer::onExit();
	log("\n----------------do onExit!--------------\n");
}

void GameUI::menuReOpen(Ref*pSender)
{
	log("reopen game!");
	SceneManager::GetInstance()->goToXXScene(0);
}
void GameUI::menuExit(Ref*pSender)
{
	log("exit game");
	Director::getInstance()->end();
}

/*-----个性化角色信息-----*/
void GameUI::initRoleInfo(PlayInfo* player)
{
	//根据传入的角色索引index 来初始化
	//主要差距在血量、技能、人物图片的不同

	//默认初始化4血
	log("\n------------ do initRoleInfo-----------\n--------------------");
	int _roleHealth = player->GetPlayerHealth();
	for (int i=0;i<_roleHealth;i++)
	{
		auto h0 = Sprite::create("pic/heart.png");
		h0->setAnchorPoint(Vec2::ZERO);
		h0->setScale(0.7);
		h0->setPosition(Director::getInstance()->getVisibleSize().width - 45, 60+i*40);
		//roleHealthInfo.pushBack(h0);
		addChild(h0,2,i);
	}


	//初始化 手牌数目显示标签
	_showOurPokerNums = Label::create("0", "fonts/Marker Felt.ttf", 22);
	_showOurPokerNums->setAnchorPoint(Vec2::ZERO);
	_showOurPokerNums->setPosition(630,15);
	pokerSlot->addChild(_showOurPokerNums, 5);
	
	
}
void GameUI::UpdateRoleInfo(PlayInfo * player)
{
	int _roleHealth = player->GetPlayerHealth();
	int _roleMaxHealth = player->GetPlayMaxHealth();

	for (int i = 0; i < _roleMaxHealth; i++)
	{	
		if (i<_roleHealth)
		{
			((Sprite*)getChildByTag(i))->setTexture("pic/heart.png");
		}
		else
		{
			((Sprite*)getChildByTag(i))->setTexture("pic/heartlose.png");
		}
		
	}
	int num = player->_playPokerSlot.size();
	_showOurPokerNums->setString(std::to_string(num));
}
void GameUI::initFoeInfo(PlayInfo* player)
{

	//初始化角色图片
	auto foePicInfo = Sprite::create("pic/head90.png");
	foePicInfo->setAnchorPoint(Vec2::ZERO);
	foePicInfo->setScale(0.8);
	foePicInfo->setPosition(2, 80);
	foeInfoShow->addChild(foePicInfo,0);
	//初始化角色血量
	int _roleHealth = player->GetPlayerHealth();
	for (int i = 0; i < _roleHealth; i++)
	{
		auto h0 = Sprite::create("pic/heart.png");
		h0->setAnchorPoint(Vec2::ZERO);
		h0->setScale(0.6);
		h0->setPosition(140, 30 + i * 30);

		foeInfoShow->addChild(h0,2,i);
	}
	
	//初始化装备槽
	auto weaponLabel = Label::createWithTTF("weapon", "fonts/Marker Felt.ttf", 14);
	auto armorLabel = Label::createWithTTF("armor", "fonts/Marker Felt.ttf", 14);
	auto horse01Label = Label::createWithTTF("defensehorse", "fonts/Marker Felt.ttf", 14);
	auto horse02Label = Label::createWithTTF("attackhorse", "fonts/Marker Felt.ttf", 14);
	weaponLabel->setAnchorPoint(Vec2::ZERO);
	armorLabel->setAnchorPoint(Vec2::ZERO);
	horse01Label->setAnchorPoint(Vec2::ZERO);
	horse02Label->setAnchorPoint(Vec2::ZERO);
	weaponLabel->setPosition(2, 62);
	armorLabel->setPosition(2, 42);
	horse01Label->setPosition(2, 22);
	horse02Label->setPosition(2, 2);
	foeInfoShow->addChild(weaponLabel,1);
	foeInfoShow->addChild(armorLabel,1);
	foeInfoShow->addChild(horse01Label,1);
	foeInfoShow->addChild(horse02Label,1);

	//初始化 手牌数目显示标签
	_showFoePokerNums = Label::create("0", "fonts/Marker Felt.ttf", 16);
	_showFoePokerNums->setAnchorPoint(Vec2::ZERO);
	_showFoePokerNums->setPosition(150, 3);
	foeInfoShow->addChild(_showFoePokerNums, 3);

}

void GameUI::UpdatFoeInfo(PlayInfo * player)
{
	//log("do updateFoeInfo!");
	int _roleHealth = player->GetPlayerHealth();
	int _roleMaxHealth = player->GetPlayMaxHealth();

	/*for (int i = _roleHealth; i < _roleMaxHealth; i++)
	{
		((Sprite*)getChildByTag(i))->setTexture("pic/heartlose.png");
	}*/
	//log("----------Foecurrenthealth=%d", _roleHealth);
	for (int i = 0; i < _roleMaxHealth; i++)
	{
		if (i < _roleHealth)
		{
			((Sprite*)foeInfoShow->getChildByTag(i))->setTexture("pic/heart.png");
		}
		else
		{
			((Sprite*)foeInfoShow->getChildByTag(i))->setTexture("pic/heartlose.png");
		}

	}

	int num = player->_playPokerSlot.size();
	_showFoePokerNums->setString(std::to_string(num));
	
}


void GameUI::menuaddpoker(Ref*pSender)
{
	isAddPoker = true;
	log("-------------mo pai ----------");
	
}
void GameUI::menuusepoker(Ref*pSender)
{
	usePoker();
}
void GameUI::menugiveuppoker(Ref*pSender)
{
	log("give up poker");
	
	giveupPoker();
}

void GameUI::menuOkPoker(Ref*pSender)
{
	isUsePoker = true;

	//log("just use this poker!");
}
void GameUI::menuCancelPoker(Ref*pSender)
{
	for (auto &w:showpokerslot)
	{
		if (w->IsSelect)
		{
			w->IsSelect = false;
			DownPoker(w);
		}
	}
	//log("i need have an consider.");
}
void GameUI::addPoker(int index01,int index02)
{
//	log("add poker!");
	if (showpokerslot.empty()!=true)
	{
		auto last = showpokerslot.end();
		auto lastPotinX = *(--last);
		//auto pr = lastPotinX->pokerPic;
		auto vec = lastPotinX->pokerPic->getPositionX();
		_lastpokerpoint = vec+95;
	}
	
	auto newpoker1 = new Poker(index01);
	auto newpoker2 = new Poker(index02);
	showpokerslot.push_back(newpoker1);
	showpokerslot.push_back(newpoker2);
	auto poker01 = newpoker1->pokerPic;
	auto poker02 = newpoker2->pokerPic;

	
	
	//牌间距应该是个变量，根据手牌数目而定，现暂时定位定值
	poker01->setPosition(815, 10);
	addChild(poker01, 10, thandPoker_Tag);
	poker02->setPosition(910, 10);
	addChild(poker02, 10, thandPoker_Tag);
	auto mov1 = MoveTo::create(1, Vec2(_lastpokerpoint, 10));
	auto mov2 = MoveTo::create(1, Vec2(_lastpokerpoint +95, 10));
	auto callbackDrawPoker = CallFunc::create(CC_CALLBACK_0(GameUI::DrawShowPokerSlot,this));
	auto pokerSeq1 = Sequence::create(mov1,callbackDrawPoker,nullptr);
	auto pokerSeq2 = Sequence::create(mov2,callbackDrawPoker,nullptr );
	poker01->runAction(pokerSeq1);
	poker02->runAction(pokerSeq2);

	//DrawShowPokerSlot();
//	log(" over addPoker in slot!");


//	log("\n-------------------------\n");
}
void GameUI::usePoker(int num)
{
	log("use poker!");
	isEndUsePokeState = true;
}

void GameUI::DrawnDarkAllPoker()
{
	for (auto &w:showpokerslot)
	{
		
		color =w->pokerPic->getDisplayedColor();
		w->pokerPic->setColor(Color3B(30, 100, 100));
	//	w->pokerPic->setColor(color);
	}
}

void GameUI::AdjustPoker()
{




	if (isSortPokers==true)//如果进行手牌排序
	{
		//do sort
	}

}






void GameUI::giveupPoker()//丢弃的牌添加到弃牌堆giveupPokerHeap 
{
//	log("giveup poker!");

	auto it=showpokerslot.end();
	Poker* pokerindex = *(--it);
	auto sp = pokerindex->pokerPic;
	auto callbackDrawPoker = CallFunc::create(CC_CALLBACK_0(GameUI::addgiveupheap,this, pokerindex));//
	sp->setTag(tgiveupPoker_Tag);
	pokerindex->pokerPic->runAction(Sequence::create(MoveTo::create(1,Vec2(360, 260)),callbackDrawPoker,nullptr));

	showpokerslot.pop_back();
	DrawShowPokerSlot();
	log("length=%d", showpokerslot.size());

}
void GameUI::giveupPoke_Robot(int index)
{
	//这个函数负责显示丢弃的牌,接收参数为丢弃牌的类型编号
	//log("show Robot  giveup poker.");
	auto mov1 = MoveTo::create(1,Vec2(360, 260));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto newpoker = new Poker(index);
	newpoker->PokerPosition(visibleSize.height - 210, visibleSize.width / 2);
	auto SpritePic = newpoker->pokerPic;
	addChild(SpritePic, 10, tgiveupPoker_Tag);
	log("runaction!");
	auto callbackDrawPoker = CallFunc::create(CC_CALLBACK_0(GameUI::addgiveupheap, this, newpoker));
	SpritePic->runAction(Sequence::create(mov1, callbackDrawPoker,nullptr));//
	//log("i don't know what fun is first");
}

void GameUI::fun1(Ref*obj)
{
	log("start call function");
	auto ptr=dynamic_cast<Sprite*>(obj);
	ptr->setVisible(false);
	delete ptr;
	log("have callfunn !");
}
/*更新弃牌堆,主要用来控制弃牌poker对象的内存释放*/
void GameUI::Updategiveupheap()
{
	//弃牌堆元素重排位置,先右后左


	
	if (isUpdateGiveupHeap&&giveupPokerHeap.empty()!=true)//确认要清除弃牌堆且弃牌堆有牌
	{
		int i = giveupPokerHeap.size();
		do 
		{
			auto first = giveupPokerHeap.begin();//获取首元素迭代器
			delete *first;//释放首元素内存
			giveupPokerHeap.pop_front();
			i--;
		} while (i>0);
		isUpdateGiveupHeap = false;
	}


}
//倒计时函数,实现延时，主要用于出牌阶段的读秒、使用和打出牌和使用技能时的读秒
void GameUI::CountDown(float timelength,int index)
{
	
	isCountDown = true;
	timebar->setVisible(true);
//	auto r = timelength * 60 / 100.0f;
	if (index==0)//出牌阶段
	{
		schedule(schedule_selector(GameUI::setTimeBarwithtime), 0.1f);
	}
	else//弃牌阶段计时
	{
		
		schedule(schedule_selector(GameUI::setTimeBarwithtimeIngiveup), 0.1f);
	}
	

}
void GameUI::setTimeBarwithtime(float dt)
{
	//每次减少20%
	auto temp = timebar->getPercent();
	temp = temp -2.0f;
	timebar->setPercent(temp);
	log("---------!!!!!!!!!!!!!!!!!!!!------------");
	//log("now percent is :%f", timebar->getPercent());
	if (timebar->getPercent()<=0.001)
	{
		if (!isExtraUsePoker)//如果不是是回合外用牌
		{
			unschedule(schedule_selector(GameUI::setTimeBarwithtime));
			isEndUsePokeState = true;//表示 时间到了 用牌阶段应该结束
			timebar->setPercent(100.0f);
			timebar->setVisible(false);
		}
		
	}
}
void GameUI::setTimeBarwithtimeIngiveup(float dt)
{
	//每次减少20%
	auto temp = timebar->getPercent();
	temp = temp - 2.0f;
	timebar->setPercent(temp);
	log("---------?????????????????------------");
	//log("now percent is :%f", timebar->getPercent());
	if (timebar->getPercent() <= 0.001)
	{

			unschedule(schedule_selector(GameUI::setTimeBarwithtimeIngiveup));
			isEndGiveUpPokeState = true;//表示 时间到了 弃牌阶段应该结束
			timebar->setPercent(100.0f);
			timebar->setVisible(false);
			

	}
}


//令当前回合进行读条的Loadingbar 指针指向play的时间读条指针
void GameUI::SwapTimeBar()
{
	//交换指针
	auto temp = timebar;
	timebar = timebarRobot;
	timebarRobot = temp;
}

void GameUI::UpdateShowPokerSlot(PlayInfo* player)
{
	/*auto beg = player->_playPokerSlot.begin();
	auto end = player->_playPokerSlot.end();
	showpokerslot.assign(beg, end);*/
	showIntslot =player->_playPokerSlot;
}

void GameUI::DrawShowPokerSlot()
{
	auto length = showpokerslot.size();
	float dis;
	if (length>=6)
	{
		dis = 570.0f / length;
	}
	else
	{
		dis = 95;
	}

	//位置排序
	std::vector<int> potinVect;
	for (int i=0;i<length;i++)
	{
		auto temp = 150+i*dis;
		showpokerslot[i]->PokerPosition(temp, 10);
		showpokerslot[i]->IsSelect = false;
		potinVect.push_back(temp);
	}
	if (potinVect.empty()!=true)
	{
		auto it = potinVect.end() - 1;
		_lastpokerpoint = *it+95;
	}

}

void GameUI::addgiveupheap(Poker* obj)
{
	log("push a poker in giveheap!");
	giveupPokerHeap.push_back(obj);
}
void GameUI::TopPoler(Poker* poker)
{

	poker->pokerPic->runAction(MoveBy::create(0.7, Vec2(0, 30)));
	poker->IsTopPoker - true;
}
void GameUI::DownPoker(Poker*poker)
{
	poker->pokerPic->runAction(MoveBy::create(0.7, Vec2(0, -30)));
	poker->IsTopPoker = false;
	menuButtonOK->setEnabled(false);
}



bool GameUI::onTouchBegan(Touch * touch, Event * event) 
{
//	log("--------touchBegin----------");
	auto ve = touch->getLocation();
//	log("obj 's position=(%f,%f)", ve.x, ve.y);

	if (isSelectShaPoker==true)//如果是要出  杀
	{
		auto size = foeInfoShow->getContentSize();

		auto nodeve = foeInfoShow->convertToNodeSpace(ve);//节点坐标
		Rect rect = Rect(0, 0, size.width,size.height);
		if (rect.containsPoint(nodeve))
		{
			//在范围内 则可以点击确定按钮出牌:满足了出牌条件
			
			menuButtonOK->setEnabled(true);
		}
	}

	if (showpokerslot.empty()!=true)
	{
		auto it = --showpokerslot.end();
		auto lastpoint = (*it)->pokerPic->getPositionX();
		auto rect = Rect(150, 10, lastpoint + 95 - 150, 140);

		if (rect.containsPoint(ve))//如果点ve在rect范围内
		{
			//继续判断在哪张牌的位置
			if (showpokerslot.size()>6)//如果手牌超过6张,意味着下方手牌(前面的poker*指向的对象)会被后面的遮盖一部分
			{
				log("poker >6");
			}
			else
			{
				for (int i=0;i<showpokerslot.size();i++)
				{
					auto temppoint = showpokerslot[i]->pokerPic->getPosition();
					
					Rect spriteRect = Rect(temppoint, showpokerslot[i]->pokerPic->getContentSize());
					
					if (spriteRect.containsPoint(ve))//判断ve是否在第i张牌的范围内
					{
						auto obj = showpokerslot[i];
						if (obj->IsCanUsableCurr)//当前能够使用
						{
						//能够使用才能被选取
							if (obj->IsSelect)
							{
								//log("do`````````````");
								DownPoker(obj);
								obj->IsSelect = false;

							}
							else
							{
								TopPoler(obj);
								obj->IsSelect = true;


							}
						}
						else
						{
							//
						}
						
					}
				}
			}
		}
		
	}




	return true;
}

void GameUI::onTouchMoved(Touch * touch, Event * event)
{
	log("--------TouchMoved----------");
	
}

void GameUI::onTouchEnded(Touch * touch, Event * event)
{
	log("--------TouchEnded----------");
}

void GameUI::onTouchCancelled(Touch * touch, Event * event)
{
	log("--------TouchCancelled----------");
}

void GameUI::isSelectPoker()
{
	log("do isSelectPoker consider");
}
