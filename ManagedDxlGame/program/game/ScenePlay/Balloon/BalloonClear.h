#pragma once
#include "../../../engine/GameEngine.h"
#include "../../SceneAll/GameObject.h"

class Player;
class Camera;
class Collision;


/////////////////////////////////////////////////////////////////////////////////////////
// 
//クリア風船クラス（描画と更新）
//
/////////////////////////////////////////////////////////////////////////////////////////


class BalloonClear : public GameObject
{

private:

	//-----------------------------------enumクラス-----------------------------------//

	enum class eBalloonState
	{
		Hidden,
		Rising,
		Floating,
		ClearRising
	};

	//--------------------------------------------------------------------------------//

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	explicit BalloonClear(Collision* collision);

	~BalloonClear() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// 点滅間隔
	const float BLINK_INTERVAL = 2.0f;
	// 風船のハンドル(Rising,Floating)
	int m_balloon_hdl = 0;
	// 風船のハンドル(ClearRising)
	int m_balloon_clear_hdl = 0;
	// ボタン操作表示のハンドル
	int m_clear_up_hdl = 0;

	// 浮遊時間
	float m_float_time = 0.0f;
	// 浮遊の座標幅
	float m_offset_y = 10.0f;
	// 浮遊の速度
	float m_velocity_y = 100.0f;
	// 操作ボタンの点滅時間
	float m_blink_time = 0.0f;

	// 風船のサイズ
	tnl::Vector3 m_size = { 300,500,0 };
	// 風船の位置(座標の後付け定義用)
	tnl::Vector3 m_target_pos;

	// 画像の切り替えフラグ
	bool m_is_change_grahic = false;
	// 描画フラグ
	bool m_is_draw = false;

	// enumクラスで各風船の画像と状態を管理（初期状態はHidden）
	eBalloonState e_balloon_state = eBalloonState::Hidden;

	// 当たり判定のポインタ
	Collision* m_collision = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// クリア座標の更新
	// tips ... Update関数内で呼び出します
	void ClearPosChange();
	// 風船の移動（クリア時の風船の演出に関する処理）
	// arg ... delta_time(前フレームからの経過時間)
	// tips ... Update関数内で呼び出します
	void MoveBalloon(float delta_time);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(float delta_time, const Camera* camera) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// クリアグラフィックへの切り替えフラグを取得
	bool GetIsChangeGraphic() const { return m_is_change_grahic; }
	// 描画フラグの設定
	// arg ... m_is_draw(描画フラグ)
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }

	//-------------------------------------------------------------------------------//
};