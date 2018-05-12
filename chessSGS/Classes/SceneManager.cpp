#include "SceneManager.h"
#include "GameUI.h"
#include "GameScene.h"
Scene* SceneManager::craetMainScene()
{
	GameScene* firstScene = GameScene::create();

	return firstScene;
}

void SceneManager::goToXXScene(int index)
{
	/*switch (index)
	{
	default:
		break;
	}*/
}
void SceneManager::playBGM(const char*pszFilePaht,bool bloop)
{

	
}