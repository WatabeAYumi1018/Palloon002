#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../../SceneAll/GameObject.h"

class Character;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// エフェクト関係の基底クラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class Effect : public GameObject
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Effect(tnl::Vector3 pos, Character* character);

	virtual ~Effect();

	//--------------------------------------------------------------------------------//

protected:

	//-----------------------------------メンバ変数-----------------------------------//

	// サイズ
	int m_size = 30;						
	
	// エフェクトの持続時間
	float m_active_time = 0.9f;				
	// 経過時間
	float m_elapsed_time = 0.0f;				

	// オフセット
	tnl::Vector3 m_offset;					

	// 活性化フラグ
	bool m_is_active = false;			

	// エフェクトの種類
	eEffectPlayerType e_type;				
	
	// 描画アニメーションポインタ
	wta::DrawAnim* m_animLoader = nullptr;
	// キャラクターポインタ
	Character *m_character = nullptr;		

	//--------------------------------------------------------------------------------//

public:

	//---------------------------------Setter&Getter---------------------------------//

	// サイズの取得
	int GetSize() const { return  m_size; }
	// オフセットの設定
	// arg ... m_offset(描画座標のオフセット)
	void SetOffset(tnl::Vector3 offset) { m_offset = offset; }
	// 行動フラグの設定
	// arg ... m_is_active(活性化フラグ)
	void SetIsActive(bool is_moved) { m_is_active = is_moved; }
	// 行動フラグの取得
	bool GetIsActive() const { return m_is_active; }

	//------------------------------------------------------------------------------//
};