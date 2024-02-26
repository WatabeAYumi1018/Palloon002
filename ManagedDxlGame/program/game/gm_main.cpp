#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "../game/ScenePlay/ScenePlay.h"
#include "../game/SceneTitle/SceneTitle.h"
#include "../engine/SceneManager.h"

//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行
void gameStart()
{
	srand(time(0));

	SetWindowText("Palloon!");
	
	SceneManager::GetInstance(new SceneTitle());
}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行
void gameMain(float delta_time)
{
	SceneManager::GetInstance()->Update(delta_time);
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行
void gameEnd()
{
	SceneManager::GetInstance()->Finalize();
}
