#pragma once
#include "../../../engine/GameEngine.h"


class Map;
class Character;
class Player;
class Enemy;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 当たり判定の識別と具体的処理を行うクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Collision
{

	//--------------------------コンストラクタ、デストラクタ--------------------------//

public:

	Collision();
	~Collision() {}

	//-------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// 前回取得したキャラクターの座標
	tnl::Vector3 m_last_chara_pos;								
	// Clear地点の座標
	tnl::Vector3 m_clear_pos;									
	
	// Clearフラグ
	bool m_is_clear=false;										
	// 上ボタン判定フラグ
	bool m_is_up = false;									    

	// 前回取得した当たり判定情報
	std::vector<std::vector<sCollisionInfo>> m_cached_chips;	

	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// キャラクターと矩形の当たり判定
	void CheckBoxCollision
	(
		Character* chara
		, Map* map
		, const std::vector<std::vector<sCollisionInfo>>& surroundingChips
	);	
	
	// キャラクターと線分の当たり判定
	void CheckLineCollision
	(
		Character* chara
		, Map* map
		, const std::vector<std::vector<sCollisionInfo>>& surroundingChips
	);	
	
	// 当たり判定が存在するか
	bool IsRowCollisionExists(const std::vector<sCollisionInfo>& rowChips);				

	// 当たり判定を取得
	std::vector<sCollisionInfo> GetRowChips
	(
		int chip_x
		, int i
		, int range
		, const Map* map
	);									
	
	// キャラクターの周囲の当たり判定を取得
	std::vector<std::vector<sCollisionInfo>> GetSurroundingChips
	(
		Character* chara
		, Map* map
		, int range
	);					

public:

	// 当たり判定の計算
	// arg1 ... キャラクターのポインタ
	// arg2 ... マップのポインタ
	// args3 ... 当たり判定検知の範囲
	// tips1 ... オブジェクトを生成しているScenePlay内で呼び出します
	// tips2 ... 当たり判定に関する処理の中で呼び出します
	void CollisionCalculate(Character* chara, Map* map, int range);			
	// キャラクター同士の当たり判定
	// arg1 ... プレイヤーのポインタ
	// arg2 ... 敵のポインタ
	// tips1 ... オブジェクトを生成しているScenePlay内で呼び出します
	// tips2 ... 当たり判定に関する処理の中で呼び出します
	void CollisionCharacter(Player* player, Enemy* enemy);
	// キャラクターのマップチップ座標を取得
	// arg1 ... キャラクターの座標
	// arg2 ... マップのポインタ
	// tips1 ... オブジェクトを生成しているScenePlay内で呼び出します
	// tips2 ... 当たり判定に関する処理の中で呼び出します
	tnl::Vector3 GetCharacterMapChipPos(const tnl::Vector3& charaPos, const Map* map);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// クリア判定を行う座標を取得
	const tnl::Vector3 GetClearPos() const { return m_clear_pos; }
	// クリア判定フラグを取得
	bool GetIsClear() const { return m_is_clear; }
	// 上ボタン判定フラグを取得
	bool GetIsUp() const { return m_is_up; }

	//---------------------------------------------------------------------------------//
};
