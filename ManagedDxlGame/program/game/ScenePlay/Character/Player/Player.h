#pragma once
#include "../../../../engine/GameEngine.h"
#include "../Character.h"

class Camera;
class Map;
class Collision;
class Wind;
class Logo;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// プレイヤークラス（一括管理）
//
/////////////////////////////////////////////////////////////////////////////////////////


class Player :public Character
{

private:

	//-----------------------------------enumクラス-----------------------------------//

	// プレイヤーのアクション
	enum class ePlayerAction
	{
		Idle_right,
		Idle_left,
		Move_right,
		Move_left,
		Dash_right,
		Dash_left,
		Hover_right,
		Hover_left,
		Hover_end_right,
		Hover_end_left,
		Stamp_right,
		Stamp_left,
		Roll_right,
		Roll_left,
		Fire_right,
		Fire_left,
		Beam_right,
		Beam_left,
	};

	//--------------------------------------------------------------------------------//

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	Player
	(
		const tnl::Vector3& initialPos
		, Collision* collision
		, Map* map
		,Wind* wind
		,Logo* logo
	);
	
	virtual ~Player() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// サイズ
	static constexpr int SIZE = 35;						
	// HP
	static constexpr int MAX_HP = 5;					
	// 移動速度（pix / fps)
	static constexpr float VELOCITY_X = 100.0f;			
	static constexpr float VELOCITY_Y = 500.0f;
	// ダッシュのしきい値
	const float DASH_THRESHOLD = 0.8f;					
	// 初期の浮遊力
	const float HOVER_FIRST_FORCE = 1.2f;	
	// 浮遊力の減衰率
	const float HOVER_DECAY_FORCE = 1.0f;				
	// 着地時のアクションの時間
	const float STAMP_TIME= 1.5f;						

	// 現在の浮遊力
	float m_hovering_force = 0.0f;						
	// 着地時のアクションのタイマー
	float m_stamp_time = 0.0f;							
	
	// 描画フラグ
	bool m_is_draw = true;								
	// 空中のフラグ
	bool m_is_hovering = false;							
	// 下降のフラグ
	bool m_is_hovered = false;							
	// スタンプアクションのフラグ
	bool m_is_stamp = false;							
	// ローリングアクションのフラグ
	bool m_is_rolling=false;							

	// 現在のアクション
	ePlayerAction e_currentAction 
		= ePlayerAction::Idle_right;

	// 当たり判定のポインタ
	Collision* m_collision = nullptr;
	// マップのポインタ
	Map* m_map = nullptr;
	// 風のポインタ（ステージ２のみ）
	Wind* m_wind = nullptr;
	// ロゴのポインタ
	Logo* m_logo = nullptr;

	//-------ゲームスティック用--------//

	// アナログスティックの傾きベクトル
	int m_input_x=0;

	int m_input_y=0;

	// x軸方向の入力の正規化
	float m_normalized_input_x = 0.0f;							
	
	//---------------------------------//

	//--------------------------------------------------------------------------------//

	
	//-----------------------------------メンバ関数-----------------------------------//

	// ゲームボタン操作の設定
	// arg... delta_time(前フレームからの経過時間)
	// tips ... この関数は、Update関数内で呼び出します
	void MoveHandle(float delta_time);
	// 入力によるアニメーションの設定
	// arg... delta_time(前フレームからの経過時間)
	// tips ... この関数は、Update関数内で呼び出します
	void ActionHandle(float delta_time);		
	// 移動範囲の制限
	// tips ... この関数は、Update関数内で呼び出します
	void MoveRange();							
	// 重力処理
	// arg... delta_time(前フレームからの経過時間)
	// tips ... この関数は、Update関数内で呼び出します
	void Gravity(float delta_time);		
	// 風の影響による処理
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... この関数は、Update関数内で呼び出します
	// tips2 ... ただし、ステージ２のみで実行されます
	void ApplyWind(float delta_time);			

	// ホバリング処理
	// arg... delta_time(前フレームからの経過時間)
	// tips ... この関数は、MoveHandle関数内で呼び出します
	void Hovering(float delta_time);			
	// ホバリング操作
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... この関数は、MoveHandle関数内で呼び出します
	// tips2 ... HoveringStartRight関数とHoveringStartLeft関数を呼び出します
	void HoveringDirection(float delta_time);	
	// ホバリング開始処理（右）
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... 向きによるアニメーション設定をします
	// tips2 ... この関数は、HoveringDirection関数内で呼び出します
	void HoveringStartRight(float delta_time);
	// ホバリング開始処理（左）
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... 向きによるアニメーション設定をします
	// tips2 ... この関数は、HoveringDirection関数内で呼び出します
	void HoveringStartLeft(float delta_time);	

public:

	// 着地時のアクション
	// arg... delta_time(前フレームからの経過時間)
	// tips ... この関数は、MoveHandle関数内で呼び出します
	void StampAction(float delta_time);		
	// ロール時のアクション
	// arg... delta_time(前フレームからの経過時間)
	// tips ... この関数は、MoveHandle関数内で呼び出します
	void RollAction(float delta_time);
	// 接地判定
	// tips ... この関数は、条件式にて当たり判定のために使用します
	bool CheckIsGround();						

	void Update(float delta_time) override;

	void Draw(float delta_time, const Camera* camera) override;

	//--------------------------------------------------------------------------------//

	
	//---------------------------------Setter&Getter---------------------------------//

	// 描画フラグの設定
	// args ... m_is_draw(描画フラグ)
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }
	// 描画フラグの取得
	bool GetIsDraw() const { return m_is_draw; }
	// スタンプアクションのフラグ設定
	// args ... m_is_stamp(スタンプアクションのフラグ)
	void SetIsStamp(bool is_stamp) { m_is_stamp = is_stamp; }
	// ローリングアクションのフラグ取得
	bool GetIsRolling() const { return m_is_rolling; }

	//--------------------------------------------------------------------------------//
};


// ※
// 今回はプレイヤーに関する処理を一括で定義しましたが、
// クラスの責任を分けることが今後の課題です。
// 描画のみを管理するplayerDrawクラス、座標移動のplayerMoveクラスなど
// １つのクラスに複数の責任を持たせないようにすることが重要と考えています。