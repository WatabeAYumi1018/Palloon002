#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 敵クラス：妖精（一括管理）
//
/////////////////////////////////////////////////////////////////////////////////////////


class EnemyFairy :public Enemy
{

private:

	//-----------------------------------enumクラス-----------------------------------//

	enum sFairyType
	{
		Peach,
		Blue,
		Yellow
	};

	//--------------------------------------------------------------------------------//

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	EnemyFairy
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		, Player* player
		, Map* map
		, Collision* collision
		, Camera* camera
	);
	
	~EnemyFairy();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// 妖精の種類（グラフィックの違い）
	sFairyType s_type;												
	// コルーチンシーケンス
	TNL_CO_SEQUENCE(EnemyFairy, &EnemyFairy::SeqIdle);						


	//-------------------------------------------------------------------------------//


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
	
	// ランダムで種類を決定
	void RandomType();														

	void Update(const float delta_time) override;	

	void Draw(const float delta_time, const Camera* camera) override;		

	//-------------------------------------------------------------------------------//
};
