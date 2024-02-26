#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/Music/MusicManager.h"

class GameObject;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ゲームセレクトのシーン（描画や更新の他、セレクト画面内での挙動も）
//
/////////////////////////////////////////////////////////////////////////////////////////


class SceneSelect : public SceneBase 
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	SceneSelect();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//
	
	//ステージ数
	const int STAGE_NUM = 4;					

	// 背景画像のハンドル
	int m_back_hdl = 0;
	// ステージ１のハンドル
	int m_stage1_hdl = 0;
	// ステージ２のハンドル
	int m_stage2_hdl = 0;
	// ステージ３のハンドル
	int m_stage3_hdl = 0;
	// ボスステージのハンドル
	int m_boss_hdl = 0;
	
	// 選択中ステージ
	int m_selected_stage = 0;					

	// 選択中風船の上下タイマー
	float m_balloon_time = 0.0f;			
	// 上下オフセット
	float m_balloon_offset_y = 10.0f;		
	// 上下速度
	float m_balloon_velocity_y = 5.0f;			

	// ステージ名
	std::vector<std::string> m_stage_names;		

	// シーケンス（選択中のステージ名）
	tnl::Sequence<SceneSelect> m_sequence
		= tnl::Sequence<SceneSelect>(this, &SceneSelect::SeqIdle);


	//-------ゲームスティック用--------//

	// 0.5秒の入力クールダウン
	const float INPUT_COUNTDOWN_TIME = 0.5f;	
	// 20%のデッドゾーン(入力無視範囲)
	const float DEADZONE = 0.2f;		

	// アナログスティックの傾きベクトル
	int m_input_x =0;

	int m_input_y =0;

	// 正規化された入力値
	float m_normalized_input_x;					
	// 入力クールダウンタイマー
	float m_input_cooldown_time = 0.0f;				
	// 前回の入力値
	float m_previous_input_x = 0.0f;

	//----------------------------------//

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//
	
	// 初期状態
	// arg... delta_time(前フレームからの経過時間)
	// tips... シーケンスにて最初に呼ばれる関数です
	bool SeqIdle(float delta_time);
	// 選択中の風船の上下移動
	// arg... delta_time(前フレームからの経過時間)
	// tips... 毎フレーム実行する関数です
	void MoveBalloon(float delta_time);			

public:

	void Update(float delta_time) override;

	void Draw(float delta_time) override;
	
	void Finalize() override;

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// 選択中のステージ名を取得
	// tips... ScenePlayのコンストラクタ引数として使用します
	// ex ...  new ScenePlay(GetSelectedStage());
	std::string GetSelectedStage() const 
	{
		return m_stage_names[m_selected_stage]; 
	};

	//--------------------------------------------------------------------------------//
};

