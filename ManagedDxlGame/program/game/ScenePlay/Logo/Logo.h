#pragma once
#include "../../SceneAll/GameObject.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// クリア、ゲームオーバーのロゴを管理するクラス
//
/////////////////////////////////////////////////////////////////////////////////////////

class Logo :public GameObject
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Logo();
	~Logo();

	//-------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// 点滅時間
	const float BLINK_ELAPSED_TIME = 2.0f;

	// 終了時のボタン表示画像
	int m_clear_botton_hdl = 0;
	// クリア時のロゴ画像
	int m_clear_logo_hdl = 0;
	// HP0になった時のロゴ画像
	int m_burst_logo_hdl = 0;
	// 落下した時のロゴ画像
	int m_fall_logo_hdl = 0;
	
	// ボタン画像のサイズ
	int m_botton_size = 150;
	// ロゴの描画サイズ(X)
	int m_result_x_size = 400;
	// ロゴの描画サイズ(Y)
	int m_result_y_size = 200;

	// 経過時間
	float m_blink_elapsed_time = 0.0f;

	// クリアフラグ
	bool m_is_clear = false;
	// 描画フラグ
	bool m_is_draw = false;

	// ロゴの種類
	eLogoType e_logo_type = eLogoType::None;

	//---------------------------------------------------------------------------------//

public:

	//-----------------------------------メンバ関数-----------------------------------//

	void Update(float delta_time) override;

	void Draw(float delta_time, const Camera* camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// クリアフラグの設定
	// arg ... m_is_clear(クリアフラグ)
	void SetIsClear(bool is_clear) { m_is_clear = is_clear; }

	// ロゴのタイプを設定
	// arg ... e_logo_type(ロゴの種類)
	void SetLogoState(eLogoType logo_state) { e_logo_type = logo_state; }

	//---------------------------------------------------------------------------------//
};
