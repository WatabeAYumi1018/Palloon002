#pragma once
#include "../engine/GameEngine.h"
#include "Effect.h"

class Player;


/////////////////////////////////////////////////////////////////////////////////////////
// 
//	プレイヤーエフェクトのクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class EffectPlayer : public Effect
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	EffectPlayer(Player *player, eEffectPlayerType effectType);

	~EffectPlayer();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// ビーム攻撃での当たり判定の5つの円の座標
	std::vector<tnl::Vector3> m_collision_circles_pos;			

	// エフェクトの種類
	eEffectPlayerType m_effectType = eEffectPlayerType::None;	
	
	// プレイヤーのポインタ
	Player* m_player = nullptr;				
	
	//---------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// ビーム攻撃の処理
	// tips ... EffectHandle関数内で呼び出します
	void EffectBeamHandle();
	// ファイア攻撃の処理
	// tips ... EffectHandle関数内で呼び出します
	void EffectFireHandle();
	// エフェクト攻撃の総括処理
	// tips ... Update関数内で呼び出します
	void EffectHandle();

public:

	// 円の座標を計算
	// tips ... Update関数内で呼び出します
	void CalculateCollisionCircles();							

	void Update(float delta_time) override;

	void Draw(float delta_time, const Camera* camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 当たり判定の5つの円の座標を取得
	std::vector<tnl::Vector3> GetCollisionCirclesPos() const 
	{
		return m_collision_circles_pos; 
	}

	//---------------------------------------------------------------------------------//
};