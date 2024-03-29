#pragma once
#include "../library/tnl_sequence.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// scene切り替え用の基底クラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class SceneBase 
{

public:
	
	//--------------------------コンストラクタ、デストラクタ--------------------------//

	SceneBase() {}
	virtual ~SceneBase() {}

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 初期化
	// tips ... コンストラクタ内で呼び出します
	virtual void Initialize() {}
	// 更新
	// arg... delta_time(前フレームからの経過時間)
	virtual void Update(float delta_time) {}
	// 描画
	// arg... delta_time(前フレームからの経過時間)
	virtual void Draw(float delta_time) {}
	// 破棄
	// tips ... デストラクタ内で呼び出します
	virtual void Finalize() {}

	//---------------------------------------------------------------------------------//
};

