#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 複数のクラスから参照するenumクラス、構造体を定義する
//
/////////////////////////////////////////////////////////////////////////////////////////


//----------------------------enum class----------------------------//

// プレイヤーエフェクトの種類
enum class eEffectPlayerType
{
	None,
	Fire,
	Beam,
};

// ボスエフェクトの種類
enum class eEffectBossType
{
	None,
	FireBall,
	Flame,
};

// マップの当たり判定の種類
enum class eMapCollisionType
{
	None,
	Box,
	Line,
	Clear,
};

// クリア、ゲームオーバー時のロゴの種類
enum class eLogoType
{
	None,
	Clear,
	Burst,
	Fall
};

//------------------------------------------------------------------//


//------------------------------構造体------------------------------//

// 当たり判定の情報
struct sCollisionInfo
{
	tnl::Vector3 s_pos;
	int s_size;
	eMapCollisionType s_type;
};

// 敵の座標情報
struct sEnemyPosData
{
	int s_type_id;
	tnl::Vector3 s_pos;
};

// 敵の情報
struct sEnemyInfo
{
	int s_id;
	std::string s_name;
	std::string s_color;
	int s_hp;
	int s_size;
};

//------------------------------------------------------------------//

