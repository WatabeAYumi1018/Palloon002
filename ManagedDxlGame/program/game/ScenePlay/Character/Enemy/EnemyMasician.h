#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 敵クラス：魔法使い（一括管理）
//
/////////////////////////////////////////////////////////////////////////////////////////


class EnemyMasician :public Enemy
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	EnemyMasician
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		, Player* player
		, Map* map
		, Collision* collision
		, Camera* camera
	);
	
	~EnemyMasician();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(EnemyMasician, &EnemyMasician::SeqIdle);						

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 無行動
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... コルーチンによって最初に呼び出されます
	// tips2 ... 関数最後にてTNL_SEQ_CO_CONTINUE;を必ず返してください
	// exe ... tnl_sequence_.change(&EnemyFairy::SeqIdle);
	bool SeqIdle(const float delta_time);
	// 移動処理
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... コルーチンによって呼び出されます
	// tips2 ... 関数最後にてTNL_SEQ_CO_CONTINUE;を必ず返してください
	// exe ... tnl_sequence_.change(&EnemyFairy::SeqMove);
	bool SeqMove(const float delta_time);
	// 攻撃処理
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... コルーチンによって呼び出されます
	// tips2 ... 関数最後にてTNL_SEQ_CO_CONTINUE;を必ず返してください
	// exe ... tnl_sequence_.change(&EnemyFairy::SeqAttack);
	bool SeqAttack(const float delta_time);
public:

	void Update(const float delta_time) override;	

	void Draw(const float delta_time, const Camera* camera) override;	

	//---------------------------------------------------------------------------------//
};