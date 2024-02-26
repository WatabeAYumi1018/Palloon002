#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 敵クラス：ドラゴン（一括管理）
//
/////////////////////////////////////////////////////////////////////////////////////////

class EnemyDoragon :public Enemy
{

public:
	
	//--------------------------コンストラクタ、デストラクタ--------------------------//

	EnemyDoragon
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		, Player* player
		, Map* map
		, Collision* collision
		, Camera* camera
	);
	
	~EnemyDoragon();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// コルーチンシーケンス
	TNL_CO_SEQUENCE(EnemyDoragon, &EnemyDoragon::SeqIdle);						

	//-------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//
	
	// 無行動
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... コルーチンによって最初に呼び出されます
	// tips2 ... 関数最後にてTNL_SEQ_CO_CONTINUE;を必ず返してください
	// exe ... tnl_sequence_.change(&EnemyDoragon::SeqIdle);
	bool SeqIdle(const float delta_time);
	// ファイアボール攻撃
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... コルーチンによって呼び出されます
	// tips2 ... 関数最後にてTNL_SEQ_CO_CONTINUE;を必ず返してください
	// exe ... tnl_sequence_.change(&EnemyDoragon::SeqFireBall);
	bool SeqFireBall(const float delta_time);								
	// フレイム攻撃
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... コルーチンによって呼び出されます
	// tips2 ... 関数最後にてTNL_SEQ_CO_CONTINUE;を必ず返してください
	// exe ... tnl_sequence_.change(&EnemyDoragon::SeqFlame);
	bool SeqFlame(const float delta_time);									

public:
	
	void Update(const float delta_time) override;	
	
	void Draw(const float delta_time, const Camera* camera) override;		

	//-------------------------------------------------------------------------------//
};