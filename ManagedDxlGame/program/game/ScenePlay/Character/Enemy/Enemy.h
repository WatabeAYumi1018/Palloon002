#pragma once
#include "../../../../library/tnl_sequence.h"
#include "../../../../engine/GameEngine.h"
#include "../Character.h"

class Collision;
class Camera;
class Player;
class Map;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 敵の基底クラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Enemy :public Character
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Enemy
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		,Player* player
		,Map*map
		,Collision * collision
		,Camera* camera
	);
	
	virtual ~Enemy() {}

	//--------------------------------------------------------------------------------//

protected:

	//-----------------------------------メンバ変数-----------------------------------//

	// ID
	int m_type_id;											
		
	// タイプ(種類)
	std::string m_type;										
	// 色
	std::string m_color;									
	
	// 攻撃中フラグ
	bool m_is_active = true;								
	// ボス攻撃中フラグ
	bool m_is_active_boss = false;							
	// ボスのファイアボール攻撃フラグ
	bool m_is_fireball = false;								
	// ボスのフレイム攻撃フラグ
	bool m_is_flame = false;

	// 敵の座標データ(構造体)
	sEnemyPosData s_date;

	// プレイヤーのポインタ
	Player* m_player = nullptr;
	// マップのポインタ
	Map* m_map = nullptr;
	// 当たり判定のポインタ
	Collision * m_collision = nullptr;
	// カメラのポインタ
	Camera* m_camera = nullptr;

	//-------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// プレイヤーとの距離計算
	float DistanceCalc();									
	
public:

	// 右への移動可能判定
	// tips ... この関数は、敵の移動処理（コルーチン）で使用する
	bool CanMoveRight();
	// 左への移動可能判定
	// tips ... この関数は、敵の移動処理（コルーチン）で使用する
	bool CanMoveLeft();

	virtual void Update(const float delta_time)  {}

	virtual void Draw(const float delta_time, const Camera* camera)  {}	

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// IDの取得
	int GetTypeID() const { return m_type_id; }

	// ボスの行動フラグの設定
	// arg ... m_is_active_boss(ボスの行動フラグ)
	void SetIsActiveBoss(const bool is_active_boss)
	{
		m_is_active_boss = is_active_boss; 
	}
	// ボスの行動フラグの取得
	bool GetIsActiveBoss() const { return m_is_active_boss; }

	// ボスのファイアボール攻撃フラグの取得
	bool GetIsFireBall() const { return m_is_fireball; }
	// ボスのフレイム攻撃フラグの取得
	bool GetIsFlame() const { return m_is_flame; }

	// 敵のデータ(構造体)の取得
	const sEnemyPosData& GetEnemyData() const { return s_date; }

	//-------------------------------------------------------------------------------//
};

// ※
// 今作は敵毎にクラスを作成しましたが、
// 分ける必要性がないと判断したため（似たようなクラスが重複してしまっているため）
// 今後は、クラスの統一を考えています。
