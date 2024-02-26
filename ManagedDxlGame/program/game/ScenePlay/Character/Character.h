#pragma once
#include "../../SceneAll/GameObject.h"
#include "../../../wta_library/wta_DrawAnim.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 味方、敵の基底クラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Character :public GameObject
{

public:
	
	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Character
	(
		const tnl::Vector3 pos
		, int size
		, int hp
		, const tnl::Vector3 velocity
	);
	
	virtual ~Character();

	//---------------------------------------------------------------------------------//

protected:

	//-----------------------------------メンバ変数-----------------------------------//

	// 当たり判定用サイズ
	int m_size;										
	// HP
	int m_hp;										
	
	// 無敵時間
	float m_invincible_time = 0.0f;					
	
	// 速度
	tnl::Vector3 m_velocity = { 100,0,0 };			
	// 重力
	tnl::Vector3 m_gravity = { 0,100,0 };			
	
	// 接地中
	bool m_is_ground = true;						
	// 死亡
	bool m_is_dead = false;							
	// 向き
	bool m_is_direction_right = true;				
	// 無敵
	bool m_is_invincible = false;					

	// 描画アニメーションポインタ
	wta::DrawAnim* m_animLoader = nullptr;		

	//---------------------------------------------------------------------------------//

public:

	//-----------------------------------メンバ関数-----------------------------------//

	// HPの減少
	// arg ... ダメージ量(基本１ずつ減らします)
	// tips ... 当たり判定に順ずる処理内にて呼び出します
	void DecreaseHP(int damage);				
	// 無敵状態にする
	// tips ... 当たり判定に順ずる処理内にて呼び出します
	void MakeInvincible();						
	// 無敵時間の処理
	// arg ... delta_time(前フレームからの経過時間)
	// tips ... Update内にて呼び出します
	void Invincible(float delta_time);			

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// 当たり判定用サイズの取得
	int GetSize() const { return m_size; }
	// HPの取得
	int GetHp() const { return m_hp; }
	// 死亡フラグの設定
	// arg ... m_is_dead(キャラクターの死亡フラグ)
	void SetIsDead(bool is_dead) { m_is_dead = is_dead; }
	// 死亡フラグの取得
	int GetIsDead() const { return m_is_dead; }
	// 向きの取得
	bool GetIsDirectionRight() const { return m_is_direction_right; }
	// 無敵時間の取得
	bool GetIsInvincible() const { return m_is_invincible; }

	//---------------------------------------------------------------------------------//
};