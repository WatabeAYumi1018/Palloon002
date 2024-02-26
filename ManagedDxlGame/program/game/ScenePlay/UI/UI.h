#pragma once
#include "../../../engine/GameEngine.h"
#include "../../SceneAll/GameObject.h"

class Camera;
class Player;
class Enemy;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// UIの処理一括を行うクラス
//
/////////////////////////////////////////////////////////////////////////////////////////

class UI : public GameObject
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	UI(Player* player, Enemy* enemy);

	virtual ~UI() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// HPバルーンの横幅
	const int BALLON_WIDTH = 65;

	// プレイヤーバルーンの描画間隔
	const int BALLON_INTERVAL_PLAYER = 70;
	// プレイヤーバルーンの描画開始Y座標
	const int BALLON_PLAYER_START_Y = 650;
	// プレイヤーバルーンの描画終了Y座標
	const int BALLON_PLAYER_END_Y = 720;

	// ボスバルーンの描画間隔
	const int BALLON_INTERVAL_BOSS = 50;
	// ボスバルーンの描画終了Y座標
	const int BALLON_BOSS_END_Y = 65;

	// プレイヤーのHPバルーン
	int m_hp_player_hdl = 0;
	// ボスのHPバルーン
	int m_hp_boss_hdl = 0;

	// HPの描画フラグ（ボスのみ描画）
	bool m_is_draw = false;

	// プレイヤーのポインタ
	Player* m_player = nullptr;
	// ボスのポインタ
	Enemy* m_enemy = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// プレイヤーのHPバルーンの描画処理
	// tips ... Draw関数内で呼び出します
	void HpPlayerBalloons();
	// ボスのHPバルーンの描画処理
	// tips ... Draw関数内で呼び出します
	void HpBossBallons();

public:

	void Initialize() override;

	void Draw(float delta_time, const Camera* camera) override;

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// 描画フラグの設定
	// arg ... m_is_draw(描画フラグ)
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }

	//--------------------------------------------------------------------------------//
};
