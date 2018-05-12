#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
class SceneManager
{

public:
	static SceneManager* GetInstance()
	{
		static SceneManager* _instance;
		return _instance;
	}
	Scene* craetMainScene();
	void goToXXScene(int index);

	void playBGM(const char*,bool);

private:
	SceneManager() {};
	SceneManager(const SceneManager&);
	SceneManager& operator=(const SceneManager&);
};

