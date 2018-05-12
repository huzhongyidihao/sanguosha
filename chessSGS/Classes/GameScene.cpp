#include "GameScene.h"
#include "GameLoop.h"
#include "GameUI.h"
#include "GameOverLayer.h"
#pragma execution_character_set("utf-8")
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	log("---gamescene----");
	//std::vector<PlayInfo*>_playerCollection;
	auto play01 = new PlayInfo(0);
	_playerCollection.push_back(play01);
	auto play02 = new PlayInfo(1);
	_playerCollection.push_back(play02);
	auto mainlayer = GameUI::create();
	_mainLayer = mainlayer;
	mainlayer->initRoleInfo(play01);
	mainlayer->initFoeInfo(play02);
	this->addChild(mainlayer);

	rifflePoker();//创建牌堆
	currentPlayer = 0;
	feedbackType = 0;
	isOverFeedback = false;
	barprect = 100.0f;
	scheduleUpdate();

	return true;
	
}
void GameScene::update(float delta)
{

	if (IsGameOver)
	{
		log("game is over!");
		CreateOverLayer();
		
	}
	UpdatePlayState();
	_mainLayer->UpdateRoleInfo(_playerCollection[0]);
	_mainLayer->UpdatFoeInfo(_playerCollection[1]);
	_mainLayer->Updategiveupheap();
		switch (PlayState)
		{
		case 0:
			_mainLayer->CurrenState->setString("准备阶段");
			
			PlayState++;
			break;
		case 1:
			_mainLayer->CurrenState->setString("判定阶段");
			
			
			PlayState++; 
			break;
		case 2:
			_mainLayer->CurrenState->setString("摸牌阶段");
			if (currentPlayer==0)
			{
				if (_mainLayer->isAddPoker==true)
				{
					auto poker01 = CurrentplayAddPoker(currentPlayer);//返回新添加到手牌的poker的类型编号
					auto poker02 = CurrentplayAddPoker(currentPlayer);
					_mainLayer->addPoker(poker01, poker02);//描绘摸两张牌到手牌 的效果
					_mainLayer->isAddPoker = false;
					_mainLayer->DrawnDarkAllPoker();
				}	
				if (_mainLayer->buttonmenu->isVisible())
				{
					//do  nothing
				
				}
				else
				{
					_mainLayer->buttonmenu->setVisible(true);
					_mainLayer->menuButtonOK->setEnabled(false);
				
				//	MenuItemImage* obj = static_cast<MenuItemImage*>(_mainLayer->buttonmenu->getChildren().at(0));
				//	obj->setEnabled(false);
					
				}
			}
			else
			{
				//log("------------the robot -------------");
				//_playerCollection[1]->losePlayHealth();//机器人的摸牌阶段 会失去一点生命
				//为机器人添加2张手牌
				auto poker01 = CurrentplayAddPoker(currentPlayer);//返回新添加到手牌的poker的类型编号
				auto poker02 = CurrentplayAddPoker(currentPlayer);

				int num = _playerCollection[0]->_playPokerSlot.size();
				_mainLayer->_showFoePokerNums->setString(std::to_string(num));
		

				_mainLayer->FoeIsUsePoker = true;
			}
			PlayState++;
			_mainLayer->isEndUsePokeState = false;
			
			break;
		case 3:
			_mainLayer->CurrenState->setString("出牌阶段");
			if (_mainLayer->isEndUsePokeState !=true)
			{
			
				//log("-------now is usepoker state!-------------");
			//倒计时  让gameui 进行倒计时并更新时间进度条
				if (_mainLayer->isCountDown==false)//是否正在计时
				{
					//log("-------now is countdown!-------------");
					_mainLayer->CountDown(5.0,0);
				}	
				if(currentPlayer==1)//即 如果是电脑的出牌回合
				{
					
					//电脑出牌
					if (_mainLayer->FoeIsUsePoker)
					{
						if (_mainLayer->timebar->getPercent() < barprect)
						{
							//log("timebar=%f", _mainLayer->timebar->getPercent());
							if (_mainLayer->timebar->getPercent() < 95)
							{
								if (_playerCollection[1]->UsableTaoPoker)
								{
									log("eat tao!");
									FoeUsePoker(0);
								}
							}
							if (_mainLayer->timebar->getPercent() < 50)
							{
								if (_playerCollection[1]->UsableShaPokerCounts > 0)
								{
									log("sha target 1!");
									FoeUsePoker(1);
								}

							}
						}
					}
					
				}
				else
				{
					
					SignUsablePoker();
					if (_mainLayer->showpokerslot.empty()!=true)//手牌不为空
					{
						UsePoker();
					}
				}

			}
			else
			{
				PlayState++;
				_mainLayer->isCountDown = false;
				_mainLayer->isUsePoker = false;
				for (auto&w : _mainLayer->showpokerslot)
				{
					//log("render current handpoker color");
					w->pokerPic->setColor(_mainLayer->color);
				}
				_playerCollection[currentPlayer]->UsableShaPokerCounts = 1;
				_mainLayer->isEndGiveUpPokeState = false;
			}
			
			break;
		case 4:
			_mainLayer->CurrenState->setString("弃牌阶段");
			
			if (currentPlayer==0)
			{
				//log("size=%d", _playerCollection[0]->_playPokerSlot.size());
				//log("_rolePokerUpper=%d", _playerCollection[0]->_rolePokerUpper);
				auto intx = _playerCollection[0]->_playPokerSlot.size() - _playerCollection[0]->GetPokerUpper();
				if (_playerCollection[0]->_playPokerSlot.size() >_playerCollection[0]->GetPokerUpper())
				{
					log("--------------需要弃牌------------");
					if (!_mainLayer->isEndGiveUpPokeState)
					{
						/*弃牌阶段可以点击所有的牌----设置所有牌为可以使用*/
						for (auto &w : _mainLayer->showpokerslot)
						{
							w->IsCanUsableCurr = true;
						}

						_mainLayer->menuButtonOK->setEnabled(true);
						if (_mainLayer->isCountDown == false)//是否正在计时
						{
							//log("-------now is countdown!-------------");
						//	_mainLayer->SwapTimeBar();
							_mainLayer->timebar->setPercent(100);
							_mainLayer->CountDown(5.0f, 1);
							
						}
					
						if (_mainLayer->isUsePoker)//如果点击了确定按钮
						{
							//获取当前选择的所有牌
							int count = 0;//弃置的牌数
							std::vector<Poker*>tempPoker;
							std::vector<int>tempPokerIndex;
							for (int i = 0; i < _mainLayer->showpokerslot.size(); i++)
							{
								if (_mainLayer->showpokerslot[i]->IsSelect)
								{
									count++;
									tempPoker.push_back(_mainLayer->showpokerslot[i]);
									tempPokerIndex.push_back(i);
								}
							}
							if (count<=intx)
							{
								/*丢弃当前选中的牌*/
								do 
								{
									auto w = tempPoker[count - 1];
								
									auto m = tempPokerIndex[count - 1];
									w->pokerPic->runAction(Sequence::create(MoveTo::create(1, Vec2(360, 260)), CallFunc::create([&, w]() {
										_mainLayer->giveupPokerHeap.push_back(w);
										log("丢弃当前选定的牌!");
									}), nullptr));

									auto _pokerbegin = _playerCollection[0]->_playPokerSlot.begin() + m;
									_playerCollection[0]->_playPokerSlot.erase(_pokerbegin);
									auto itbegin = _mainLayer->showpokerslot.begin() + m;
									_mainLayer->showpokerslot.erase(itbegin);
									_mainLayer->DrawShowPokerSlot();
									count--;
								} while (count>0);
								

							}
							else
							{
								//操作失败
							}
							_mainLayer->isUsePoker = false;
						}
					}
					else
					{
						CurrentplayGiveupPoker(currentPlayer);
					}
				}
				else
				{
					_mainLayer->isEndGiveUpPokeState = true;
					if (_mainLayer->isCountDown==true)
					{
						//unschedule(schedule_selector(GameUI::setTimeBarwithtimeIngiveup));  不知道为什么取消不了
						_mainLayer->timebar->setPercent(0);
						_mainLayer->setTimeBarwithtimeIngiveup(0);
					}

					//_mainLayer->timebar->setPercent(100);
					//_mainLayer->timebar->setVisible(false);
					_mainLayer->menuButtonOK->setEnabled(false);
				}
				

			//	log("------------PlayeState=%d", PlayState);
			}
			else
			{
				CurrentplayGiveupPoker(currentPlayer);
				//_playerCollection[0]->losePlayHealth();//玩家 失去一点生命
				//log("----------On! i'm lose a heat! i'm olny %d------------", _playerCollection[0]->GetPlayerHealth());
			}
			if (PlayState<=4)
			{
				if (currentPlayer==0&&!_mainLayer->isEndGiveUpPokeState)
				{
					log("-----------正在进行弃牌阶段---------");
				}
				else
				{
					PlayState = 0;
					_mainLayer->isCountDown = false;
					UpdateCurrentPlayer();//轮到下一个玩家
				}

			//	log("------------PlayeState=%d", PlayState);
			}
			break;
		case 5:
			
			GameOver();
			break;
		case 6://额外回合,回合外响应
			SignUsablePoker();
			UsePoker();
			for (int i=0;i< _mainLayer->showpokerslot.size();i++)//查看是否有选择牌
			{
				if (_mainLayer->showpokerslot[i]->IsSelect)
				{
					_mainLayer->menuButtonOK->setEnabled(true);//有 则激活按钮
					break;
				}	
				else
				{
					_mainLayer->menuButtonOK->setEnabled(false);
				}
			}
			
			/*判断是否做出响应的响应*/
			switch (feedbackType)
			{
			case 0://要出闪		
				if (isOverFeedback)
				{
						//完成响应


						//
						_mainLayer->isExtraUsePoker = false;
						_mainLayer->timebar->setPercent(100.0f);
						_mainLayer->timebar->setVisible(false);
						_mainLayer->buttonmenu->setVisible(false);
						_mainLayer->SwapTimeBar();
						_mainLayer->timebar->setVisible(true);

						_mainLayer->FoeIsUsePoker = true;
						isOverFeedback = false;
				}
				else
				{




					if (!_mainLayer->isExtraUsePoker)
					{
						_playerCollection[0]->losePlayHealth();
					}
				}
			


				break;
			case 1://要出杀杀
				break;
			case 2://要出无懈可击
				break;
			default:
				break;
			}
			if (!_mainLayer->isExtraUsePoker)
			{
				PlayState = 3;
			}
			break;
		default:
			log("have an error!");
			break;
		}



	//count++;
	//if (count >= 1200)
	//{
	//	UpdateCurrentPlayer();
	//}
}

GameScene::~GameScene()
{
	
}

//更新所有玩家的状态,主要用来鉴别是否死亡
void GameScene::UpdatePlayState()
{
	for (auto &w:_playerCollection)
	{
		if (w->GetPlayerHealth()<=0)
		{
			w->SetPlayState();//设置玩家状态为 死亡  
			PlayState = 5;//有玩家死亡，结束游戏flag触发
		}
	}
	//更新当前回合玩家状态
	auto player = _playerCollection[currentPlayer];//获取当前回合玩家信息指针
	if (player->GetPlayMaxHealth()>player->GetPlayerHealth())//如果不是满血
	{
		log("最大生命=%d", player->GetPlayMaxHealth());
		log("当前生命=%d", player->GetPlayerHealth());
		player->UsableTaoPoker = true;//可以使用桃 
		
	}
	else
	{
		player->UsableTaoPoker = false; 
		
	}

}
//标记手牌能使用的牌,根据当前回合来决断
void GameScene::SignUsablePoker()
{
	if (PlayState == 3||PlayState==6)//如果是出牌阶段或者额外阶段
	{
		auto currplaypokerslot = _mainLayer->showpokerslot;
		auto playindex = _playerCollection[currentPlayer];
		for (auto &w: currplaypokerslot)
		{
			switch (w->pokerid)
			{
			case 0://桃
				if (playindex->UsableTaoPoker)//如果能使用桃
				{

					//将桃牌标记
					w->pokerPic->setColor(_mainLayer->color);
					w->IsCanUsableCurr = true;
				}
				else
				{
					w->pokerPic->setColor(Color3B(30, 100, 100));
					w->IsCanUsableCurr = false;
				}
				break;
			case 1://杀
				//log("should sign SHA poker");
				if (playindex->UsableShaPokerCounts>0)//如果还能用杀
				{
					
					//将杀牌标记
					w->pokerPic->setColor(_mainLayer->color);
					w->IsCanUsableCurr = true;
				}
				else
				{
					w->pokerPic->setColor(Color3B(30, 100, 100));
					w->IsCanUsableCurr = false;
				}
				break;
			case 2://闪 
					//将决斗牌标记
				if (_mainLayer->isExtraUsePoker)
				{
					w->pokerPic->setColor(_mainLayer->color);
					w->IsCanUsableCurr = true;
				}
				
				break;
			default:
				break;
			}
		}
	}
	else
	{
		log("need to develop");
	}

}

void GameScene::rifflePoker()
{
	//清楚旧牌堆,新建牌堆
	if (!_pokerHeap.empty())
	{
		_pokerHeap.clear();//清楚所有元素
		log("have clear all met");
	}
	
	//暂定 一共20张牌 
	/*
	基本牌 0桃 1杀   2决斗，其中5桃12杀3决斗
	*/
	_pokerHeap={ 0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2 };
	int x = 19;
	do 
	{
		//随机交换2个下标的值
		auto index1 = random(0, 19);
		auto index2 = random(0, 19);
		if (index1!=index2)
		{
			auto temp = _pokerHeap[index1];
			_pokerHeap[index1] = _pokerHeap[index2];
			_pokerHeap[index2] = temp;
			x--;
		}

	} while (x>0);
	log("完成新建牌堆");
}

void GameScene::UpdateCurrentPlayer()//回合更替
{
	count = 1;
	
	if (currentPlayer==0)
	{
		_mainLayer->buttonmenu->setVisible(false);
		
		currentPlayer++;
		_mainLayer->SwapTimeBar();
	}
	else
	{
		currentPlayer = 0;

		barprect = 100.0f;
		_mainLayer->SwapTimeBar();
	}
	_mainLayer->isAddPoker = true;
}

void GameScene::GameOver()
{
	//游戏结束条件
	if (PlayState==5)
	{
		IsGameOver = true;
	}

}

int GameScene::GetOutPokerFromHeap()//从牌堆抽牌
{
	if (_pokerHeap.size()<=0)
	{
		//需要一个新牌堆
		rifflePoker();
	}
	log("牌堆还有%d",_pokerHeap.size());
	auto it = _pokerHeap.end();
	auto temp = *(--it);//牌堆最后一张牌,就是最上面的牌
	_pokerHeap.pop_back();
	return temp;
}

int GameScene::CurrentplayAddPoker(int index)
{
	auto temp = GetOutPokerFromHeap();
	if (_playerCollection.empty()!=true)
	{

		_playerCollection[index]->_playPokerSlot.push_back(temp);//放入手牌
		log("当前玩家:%d 拥有 %d 张手牌", index,_playerCollection[index]->_playPokerSlot.size());
	
	}
	return temp;
}

void GameScene::CurrentplayGiveupPoker(int playindex)
{
	if (_playerCollection.empty() != true)
	{
		auto upper = _playerCollection[playindex]->GetPokerUpper();
		if (_playerCollection[playindex]->_playPokerSlot.size() > upper)//判断手牌是否超限
		{
			//do give up 暂时丢弃最后的牌
			auto dis = _playerCollection[playindex]->_playPokerSlot.size() - upper;//需要丢弃的牌数

			do 
			{
				//依据Index 执行gameUI的丢弃牌 动画
				if (playindex==0)
				{
					_mainLayer->giveupPoker();
				}
				else
				{
					auto it=_playerCollection[playindex]->_playPokerSlot.end();
					log(" -----------callfunction  give up robot-------");
					_mainLayer->giveupPoke_Robot(*(--it));
				}
				_playerCollection[playindex]->_playPokerSlot.pop_back();
				dis--;
			} while (dis>0);
			

		}
		//log("-------have no give up poker!--------");
	}
	
}

void GameScene::UsePoker()//前提是已经有牌 
{
	int count = 0;
	std::vector<Poker*>tempPoker;
	std::vector<int>tempPokerIndex;
	for (int i=0;i<_mainLayer->showpokerslot.size();i++)
	{
		if (_mainLayer->showpokerslot[i]->IsSelect)
		{
			count++;
			tempPoker.push_back(_mainLayer->showpokerslot[i]);
			tempPokerIndex.push_back(i);
		}
	}
	if (count>_mainLayer->SelectPokerCounts)
	{
		//出牌无效,需要取消一些牌的选择
	}
	else
	{
		
		switch (count)
		{
		case 1:
		{
			
			switch (tempPoker[0]->pokerid)
			{
			case 0://桃
				_mainLayer->menuButtonOK->setEnabled(true);//桃可以点击自然满足出牌条件
				UseTaoPoker(tempPoker[0], tempPokerIndex[0]);
				break;
			case 1://杀
			
				
				_mainLayer->isSelectShaPoker = true;
				UseShaPoker(tempPoker[0], tempPokerIndex[0]);
				
				break;
			case 2://闪
				
				UseShanPoker(tempPoker[0], tempPokerIndex[0]);
				break;
			default:
				break;
			}
		}
			break;
		default:
			break;
		}
	}

}



void GameScene::CreateOverLayer()
{

	_overLayer = GameOverLayer::create();

	addChild(_overLayer, 10);

}

void GameScene::UseAnPokerThenUp(Poker *obj, int index)
{
	if (_mainLayer->isExtraUsePoker)
	{
		//如果是回合外出牌
		auto it_scene = _playerCollection[0]->_playPokerSlot.begin() + index;
		log("what's wrong!---------");
		_playerCollection[0]->_playPokerSlot.erase(it_scene);
	}
	else
	{
		auto it_scene = _playerCollection[currentPlayer]->_playPokerSlot.begin() + index;
		log("what's wrong!---------");
		_playerCollection[currentPlayer]->_playPokerSlot.erase(it_scene);
	}
	

	auto sp = obj->pokerPic;
	auto f = CallFunc::create([&, obj]() {
		log("弃牌堆大小=%d",_mainLayer->giveupPokerHeap.size());
		_mainLayer->giveupPokerHeap.push_back(obj);
		log("弃牌堆大小=%d", _mainLayer->giveupPokerHeap.size());
	
	});

	sp->setTag(tgiveupPoker_Tag);
	obj->pokerPic->runAction(Sequence::create(MoveTo::create(1, Vec2(360, 260)), f, nullptr));
	auto it_UI = _mainLayer->showpokerslot.begin() + index;
	_mainLayer->showpokerslot.erase(it_UI);

	//更新手牌
	_mainLayer->DrawShowPokerSlot();
	log("更新手牌槽");
}

/*牌的效果*/
void GameScene::UseTaoPoker(Poker*obj,int index)
{
	if (_mainLayer->isUsePoker)//如果点击了确定,那么就出牌,使用这张牌
	{
		//效果是
		PokerEffect(0);
		_playerCollection[currentPlayer]->recovePlayHealth();//恢复一点血
		_mainLayer->isUsePoker = false;
		log("当前玩家=%d", currentPlayer);

		UseAnPokerThenUp(obj, index);
		
	}
	log("-----------\length:=%d\n------------",_mainLayer->showpokerslot.size());
}
void GameScene::UseShaPoker(Poker*obj, int index)
{


	if (_mainLayer->isUsePoker)//如果点击了确定,那么就出牌,使用这张牌
	{
		//效果是 使目标玩家(电脑)进入 "回合外相应阶段" :在其他玩家回合内的"出牌阶段"
		
		PokerEffect(1);
		extraUsePoker(1);//1号玩家(就是电脑)响应

		_playerCollection[currentPlayer]->UsableShaPokerCounts--;//杀的使用次数-1
		_mainLayer->isUsePoker = false;
	
		UseAnPokerThenUp(obj, index);
	}

}
void  GameScene::UseShanPoker(Poker*obj, int index)
{
	if (_mainLayer->isUsePoker)//如果点击了确定,那么就出牌,使用这张牌
	{
		//效果是
		PokerEffect(2);
		isOverFeedback = true;
		_mainLayer->isUsePoker = false;

		UseAnPokerThenUp(obj, index);
	}
	log("-----------\n--use Shan --\n------------");
}

void GameScene::PokerEffect(int typeindex)
{
	Sprite*sp;
	switch (typeindex)
	{
	case 0:
		sp = Sprite::create("pic/tao_eff.png");
		break;
	case 1:
		sp = Sprite::create("pic/sha_eff.png");
		break;
	case 2:
		sp = Sprite::create("pic/shan_eff.png");
		break;
	default:
		break;
	}

		
		sp->setAnchorPoint(Vec2::ZERO);
		sp->setPosition(500, 200);
		addChild(sp, 14,1001);

		sp->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([&]() {this->removeChildByTag(1001);
		//log("----------remove ------------");
		}), nullptr));
		

}

void GameScene::extraUsePoker(int target)
{
	if (target==0)//如果目标是玩家
	{
		//
		if (_playerCollection[0]->_playPokerSlot.empty()==true)
		{
			_playerCollection[0]->losePlayHealth();//玩家 失去一点生命
			
		}
		else
		{
			if (_mainLayer->isExtraUsePoker == false)
			{
				_mainLayer->timebar->setVisible(false);//隐藏电脑的进度条
				_mainLayer->SwapTimeBar();//交换进度条指针
				_mainLayer->timebar->setVisible(true);//显示玩家的进度条 ,当前timebar指针指向玩家的
				_mainLayer->buttonmenu->setVisible(true);
				_mainLayer->menuButtonOK->setEnabled(false);

				PlayState = 6;
			}
	
			_mainLayer->isExtraUsePoker = true;
		}

	}
	else
	{

		auto temp = _playerCollection[target]->_playPokerSlot;
		
		if (temp.end()!=std::find(temp.begin(),temp.end(),2))
		{
			//如果有闪
			auto itindex = std::find(_playerCollection[target]->_playPokerSlot.begin(), _playerCollection[target]->_playPokerSlot.end(), 2);
			log("打出一张闪1");
			_playerCollection[1]->_playPokerSlot.erase(itindex);
			log("打出一张闪2");
			_mainLayer->giveupPoke_Robot(2);
			log("打出一张闪3");
		}
		else
		{
			//log("Foecurrenthealth=%d",_playerCollection[target]->GetPlayerHealth());
			_playerCollection[target]->losePlayHealth();//失去一点生命
			//log("Foecurrenthealth=%d", _playerCollection[target]->GetPlayerHealth());
		}
		log("------- extraUsePoker------");
	}
}

void GameScene::FoeUsePoker(int index)
{
	auto temp = _playerCollection[1]->_playPokerSlot;//获取手牌
	int taoindex = -1;
	int shaindex = -1;
	int shanindex = -1;
	bool havetao = false;
	bool havesha = false;
	bool haveshan = false;
	for (int k = 0; k < temp.size(); k++)
	{
		if (temp[k] == 0)//如果找到了一张桃 牌
		{
			havetao = true;
			taoindex =k;
		}
		if (temp[k] == 1)//如果找到了一张杀 牌
		{
			havesha = true;
			shaindex = k;
		}
		if (temp[k] == 2)//如果找到了一张闪 牌
		{
			haveshan = true;
			shanindex = k;
		}
	}
	switch (index)
	{
	case  0:
		//优先补满自身状态
		if (_playerCollection[1]->UsableTaoPoker&&havetao)//如果能吃桃,说明状态不满，并且还要有桃
		{
			
			//出桃牌

			PokerEffect(0);

		//	log("---------pokersize()=%d", _playerCollection[1]->_playPokerSlot.size());
			auto it = _playerCollection[1]->_playPokerSlot.begin() + taoindex;
			_playerCollection[1]->_playPokerSlot.erase(it);
			_playerCollection[currentPlayer]->recovePlayHealth();//恢复一点血
			_playerCollection[1]->UsableTaoPoker = false;
			_mainLayer->giveupPoke_Robot(0);//对电脑来说,出牌即丢一张牌到弃牌堆，这里显示丢弃一张桃
			
			

			barprect = _mainLayer->timebar->getPercent();//出牌之后储存进度
			barprect = barprect - 15.0;
			
			
		}
		break;
	case 1:
		if (_playerCollection[1]->UsableShaPokerCounts>0 && havesha)//如果有杀的使用次数并且有杀的话
		{
			auto temp1 = _playerCollection[1]->_playPokerSlot;
			//出杀
			
			auto it = _playerCollection[1]->_playPokerSlot.begin() + shaindex;
			_playerCollection[1]->_playPokerSlot.erase(it);



			_mainLayer->giveupPoke_Robot(1);
			PokerEffect(1);
			
			extraUsePoker(0);//1号玩家(就是电脑)响应
			_mainLayer->FoeIsUsePoker = false;//不能出牌,必须等待目标完成响应才能FoeIsUsePoker = true;
			
			_playerCollection[currentPlayer]->UsableShaPokerCounts--;//杀的使用次数-1
			

			barprect = _mainLayer->timebar->getPercent();//出牌之后储存进度
			barprect = barprect - 10.0;
		}
		break;
	default:
		break;
	}
	
	
	
}

