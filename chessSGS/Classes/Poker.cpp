#include "Poker.h"
USING_NS_CC;

//Poker* Create(int index)
//{
//	Poker* ref = new Poker(index);
//	if (ref&&ref->init())
//	{
//		ref->autorelease();
//		return ref;
//	}
//	else
//	{
//		delete ref;
//		ref = nullptr;
//		return nullptr;
//	}
//}

Poker::Poker(int index):IsSelect(0),IsTopPoker(0), IsCanUsableCurr(0)
{

	CreateSpecificPoker(index);
	//根据返回的标识初始化卡牌的其他信息
	name = "null";
	descir = "have no descir!";

	pokerPic->setAnchorPoint(Vec2::ZERO);

	//if (pokerPic!=nullptr)
	//{
	//	log("can able to create listener!");
	//	listener = EventListenerTouchOneByOne::create();
	//	listener->setSwallowTouches(false);
	//	listener->onTouchBegan = CC_CALLBACK_2(Poker::touchBegin, this);
	//	listener->onTouchMoved = CC_CALLBACK_2(Poker::touchMove, this);
	//	listener->onTouchEnded = CC_CALLBACK_2(Poker::touchEnd, this);
	//	listener->onTouchCancelled = CC_CALLBACK_2(Poker::touchCancelled, this);

	//	eventdispatcher = Director::getInstance()->getEventDispatcher();
	//	//eventdispatcher->addEventListenerWithFixedPriority(listener, 2);
	//	eventdispatcher->addEventListenerWithSceneGraphPriority(listener, pokerPic);
	//}

}


Poker::~Poker()
{

	//eventdispatcher->removeEventListener(listener);
	log("this is xigou function!");
}

//bool Poker::init()
//{
//	log("init poker!");
//	if (!Sprite::init())
//	{
//		return false;
//	}
//
//	return true;
//}

void Poker::PokerPosition(float x,float y)
{
	pokerPic->setPosition(Vec2(x,y));
}

//Sprite* Poker::getSprite()
//{
//	return pokerPic;
//}
void Poker::CreateSpecificPoker(int index)
{

	switch (index)
	{
	case 0://构建桃
		   //暂时硬编码
		pokerPic = Sprite::create("pic/poker_jb_00.png");
		name = "tao";//返回特定的牌的标识
		pokerid = 0;
		break;

	case 1://构建杀
	//	if (count==0)
	//	{
			pokerPic = Sprite::create("pic/poker_jb_01.png");
			name = "sha";//返回特定的牌的标识
			pokerid = 1;
	//	}
	//	else
	//	{
	//		pokerPic = Sprite::create("pic/poker_jb_01.png");
	//		name = "fangyuma";//返回特定的牌的标识
	//		pokerid = 100;
	//	}
	//	log("pokerid=%d", pokerid);
		break;
	case 2://构建     /锦囊牌决斗/   现在替换为闪

		pokerPic = Sprite::create("pic/poker_jb_02.png");
		name = "shan";//返回特定的牌的标识
		pokerid = 2;
		break;
	case 3://构建武将牌
		if (count == 0)
		{
			pokerPic = Sprite::create("pic/poker_jb_00.png");
			name = "superkongming";//返回特定的牌的标识
		}
		else
		{
			pokerPic = Sprite::create("pic/poker_jb_01.png");
			name = "superlvmeng";//返回特定的牌的标识
		}
		break;
	case 4://构建身份牌
		if (count == 0)
		{
			pokerPic = Sprite::create("pic/poker_id_00.png");
			name = "zhugong";//返回特定的牌的标识
		}
		else
		{
			pokerPic = Sprite::create("pic/poker_id_01.png");
			name = "fanzei";//返回特定的牌的标识
		}
		break;
	default:
		log(" \n-----error!------\n");
		break;

	}


}

bool Poker::touchBegin(Touch * touch, Event * event)
{
	//log("---------touchbegin----------");
	//auto vec=touch->getLocation();
	//log("UIposition is:(%f,%f)",vec.x,vec.y);
	//Vec2 point=Director::getInstance()->convertToGL(touch->getLocationInView());
	//log("Wposition is:(%f,%f)", point.x, point.y);
	auto ve = this->pokerPic->getPosition();
	log("obj 's position=(%f,%f)", ve.x, ve.y);
	//获得当前牌的位置可以得出手牌数,因为最后一张牌优先级最高,当前牌就是最后一张被描绘的牌 从150-ve.x 
	Vec2 touchpoint = touch->getLocation();
	if (touchpoint.x>150&&touchpoint.x<ve.x)
	{
		if (touchpoint.y>10&&touchpoint.y<130)
		{
			log("-----------clik on poker------------");
			
			//根据点击位置判断哪种牌
			//touchpoint.x
			//if (IsTopPoker!=true)
			//{
			//	pokerPic->runAction(MoveBy::create(0.7, Vec2(0, 30)));
			//	IsTopPoker = true;

			//}
			
		}
	}


	return true;
}

void Poker::touchMove(Touch * touch, Event * event)
{
	log("-----------touchMove-----------");
}

void Poker::touchEnd(Touch * touch, Event * event)
{
	log("------------touchEnd------------");
}

void Poker::touchCancelled(Touch * touch, Event * event)
{
	log("touchCancelled");
}
