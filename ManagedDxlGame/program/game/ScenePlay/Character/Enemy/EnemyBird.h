#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 敵クラス：鳥（一括管理）
//
/////////////////////////////////////////////////////////////////////////////////////////


class EnemyBird :public Enemy
{

public:
	
	//--------------------------コンストラクタ、デストラクタ--------------------------//

	EnemyBird
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		, Player* player
		, Map* map
		, Collision* collision
		, Camera* camera
	);
	
	~EnemyBird();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(EnemyBird, &EnemyBird::SeqMove);						

	//-------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 移動処理
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... コルーチンによって最初に呼び出されます
	// tips2 ... 関数最後にてTNL_SEQ_CO_CONTINUE;を必ず返してください
	// exe ... tnl_sequence_.change(&EnemyBird::SeqMove);
	bool SeqMove(const float delta_time);
	// 攻撃処理
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... コルーチンによって呼び出されます
	// tips2 ... 関数最後にてTNL_SEQ_CO_CONTINUE;を必ず返してください
	// exe ... tnl_sequence_.change(&EnemyBird::SeqAttack);
	bool SeqAttack(const float delta_time);

public:

	void Update(const float delta_time) override;

	void Draw(const float delta_time, const Camera* camera) override;

	//-------------------------------------------------------------------------------//
};

// ※
// 現在は未完成だが、今後改めて実装する予定です