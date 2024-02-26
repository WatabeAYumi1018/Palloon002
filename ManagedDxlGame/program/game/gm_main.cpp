#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "../game/ScenePlay/ScenePlay.h"
#include "../game/SceneTitle/SceneTitle.h"
#include "../engine/SceneManager.h"

//------------------------------------------------------------------------------------------------------------
// �Q�[���N�����ɂP�x�������s
void gameStart()
{
	srand(time(0));

	SetWindowText("Palloon!");
	
	SceneManager::GetInstance(new SceneTitle());
}

//------------------------------------------------------------------------------------------------------------
// ���t���[�����s
void gameMain(float delta_time)
{
	SceneManager::GetInstance()->Update(delta_time);
}

//------------------------------------------------------------------------------------------------------------
// �Q�[���I�����ɂP�x�������s
void gameEnd()
{
	SceneManager::GetInstance()->Finalize();
}
