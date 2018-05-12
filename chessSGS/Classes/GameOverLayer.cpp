#include "GameOverLayer.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
bool GameOverLayer::init()
{
	if (!LayerColor::init())
	{
		return false;
	}
	auto color = cocos2d::Color3B(120, 150, 230);
	
	this->setColor(color);
	this->setOpacity(10);

	//
	MenuItemFont::setFontSize(50);
	auto menuItemRepp = MenuItemFont::create("repPlayGame", CC_CALLBACK_1(GameOverLayer::menuRepPlay, this));
	auto menuItemExit = MenuItemFont::create("ExitGame", CC_CALLBACK_1(GameOverLayer::menuExit, this));
	Menu*menu = Menu::create(menuItemRepp, menuItemExit, nullptr);
	menu->alignItemsHorizontallyWithPadding(30);
	menu->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
	this->addChild(menu);

	return true;
}

void GameOverLayer::onEnter()
{
	LayerColor::onEnter();
}

void GameOverLayer::onExit()
{
	LayerColor::onExit();
}

void GameOverLayer::update(float delta)
{
}

void GameOverLayer::menuRepPlay(Ref * pSender)
{
	log("repplaygame!");
}

void GameOverLayer::menuExit(Ref * pSender)
{
	log("just exit game!");
	Director::getInstance()->end();
}
