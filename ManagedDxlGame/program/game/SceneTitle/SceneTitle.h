#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/Music/MusicManager.h"
#include "../SceneAll/Balloon/Balloon.h"

class GameObject;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// ゲームタイトルのシーン（描画や更新の他、タイトル内での挙動も）
//
/////////////////////////////////////////////////////////////////////////////////////////


class SceneTitle : public SceneBase 
{

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// 最大バウンド回数
	const int MAX_BOUNDE = 2;							
	// 地面のY位置
	const float GROUND_Y = 50;							
	// バウンド時の速度の減少率
	const float BOUND_RATE = -1.0f;						
	// ロゴの表示時間
	const float DISPLAY_TIME = 100;	
	// 風船の生成数
	const int BALLOON_SPAWN = 20;						
	// 風船の生成間隔
	const float SPAWN_INTERVSL = 0.5f;					

	// 背景のハンドル
	int m_back_hdl = 0;
	// タイトルロゴのハンドル
	int m_logo_hdl = 0;
	// キャラクターのハンドル
	int m_palloon_hdl = 0;	
	// キャラクターのバウンド回数
	int m_bound_count = 0;
	
	// ロゴの表示幅
	float m_current_width = 0;
	// ロゴの描画時間
	float m_balloon_spawn_timer = 0.0f;

	// ロゴの表示フラグ
	bool m_is_logo_displayed = false;

	// イラストの初期Y位置。画面外上部に設定
	tnl::Vector3 m_chara_pos = { 0,-360,0 };		
	// 初期の下向きの速度
	tnl::Vector3 m_velocity = {0,1,0};		
	// 重力の強さ
	tnl::Vector3 m_gravity = {0,0.1f,0};				
	
	// バルーンの配列
	std::vector<Balloon> balloons;						

	// シーケンス
	tnl::Sequence<SceneTitle> m_sequence 
		= tnl::Sequence<SceneTitle>(this, &SceneTitle::SeqIdle);

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 初期状態
	// arg... delta_time(前フレームからの経過時間)
	// tips... シーケンスにて最初に呼ばれる関数です
	bool SeqIdle(float delta_time);

	// ロゴの表示
	// arg... delta_time(前フレームからの経過時間)
	// tips... ロゴの処理を毎フレーム行います
	void LogoHandle(float delta_time);					
	// バウンドの処理
	// arg... delta_time(前フレームからの経過時間)
	// tips... バウンドの処理を毎フレーム行います
	void BoundHandle(float delta_time);				
	// バルーンの生成
	// tips ... SeqIdle関数実行時、isStart()によって一度だけ呼ばれます
	void SpawnBalloon();							

public:

	void Update(float delta_time) override;

	void Draw(float delta_time) override;
	
	void Finalize() override;

	//--------------------------------------------------------------------------------//
};
