#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/GameObject.h"
#include "../SceneAll/Music/MusicManager.h"


class BackGround;
class Camera;
class Map;
class Collision;
class BalloonInstruction;
class BalloonClear;
class EnemyLoad;
class Enemy;
class Player;
class EffectPlayer;
class EffectBoss;
class Wind;
class UI;
class Logo;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// scene内で必要な全ての要素を管理するクラス
// ポリモーフィズムのため、干渉し合う実装もここで行う（当たり判定など）
//
/////////////////////////////////////////////////////////////////////////////////////////


class ScenePlay : public SceneBase 
{

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	explicit ScenePlay(const std::string& stageName);

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------メンバ変数-----------------------------------//
	

	// ステージ３での敵の最大再生成回数
	const int ENEMY_TOTAL_RESPAWNS = 10;								

	// 敵の再生成回数をカウント
	int m_enemy_respawn_count = 0;									
	// 敵の再生成時間
	float m_enemy_respawn_time= 0.0f;									

	// シーン変更フラグ
	bool m_is_change_scene = false;
	// エフェクトフラグ
	bool m_is_effect = false;

	// ステージ名
	std::string m_stage_name;

	// 生成したオブジェクト用のリスト
	std::list<GameObject*> m_gameObjects;						
	// 生成した敵用のリスト
	std::list<Enemy*> m_enemies;								
	// 削除予定の敵用のリスト
	std::list<Enemy*> m_enemies_remove_list;					
	// 敵のIDと情報のペア(生成する敵の種類をIDで管理するため)
	std::map<int, sEnemyInfo> m_enemy_infos;					
	// リスポーンする敵のポインタと再生成までの秒数
	std::list<std::pair<Enemy*, float>> m_enemies_respawn_list;	
	
	// シーケンス
	tnl::Sequence<ScenePlay> m_sequence 
		= tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqIdle);

	// 背景のポインタ
	BackGround* m_backGround = nullptr;
	// カメラのポインタ
	Camera* m_camera = nullptr;
	// マップのポインタ
	Map* m_map = nullptr;
	// 当たり判定のポインタ
	Collision* m_collision = nullptr;
	// 操作説明バルーンのポインタ
	BalloonInstruction* m_balloonInstruction = nullptr;
	// クリアバルーンのポインタ
	BalloonClear* m_balloonClear = nullptr;
	// 敵の情報の読み取り
	EnemyLoad* m_enemyLoad = nullptr;
	// 敵のポインタ
	Enemy* m_enemy = nullptr;
	// プレイヤーのポインタ
	Player* m_player = nullptr;
	// プレイヤーエフェクトのポインタ（ビーム攻撃）
	EffectPlayer* m_effectPlayer_beam = nullptr;
	// プレイヤーエフェクトのポインタ（ファイア攻撃）
	EffectPlayer* m_effectPlayer_fire = nullptr;
	// ボスエフェクトのポインタ
	EffectBoss* m_effectBoss = nullptr;
	// 風のポインタ（ステージ２）
	Wind* m_wind = nullptr;
	// UIのポインタ
	UI* m_ui = nullptr;
	// ロゴのポインタ
	Logo* m_logo = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 初期状態
	// arg... delta_time(前フレームからの経過時間)
	// tips... シーケンスにて最初に呼ばれる関数です
	bool SeqIdle(float delta_time);

	// 敵の情報の読み取りと初期化
	// tips ... Initialize関数内で呼び出します
	void InitEnemy();
	// 音楽情報の読み取りと初期化
	// tips ... SeqIdle関数のisStart関数内で呼び出します
	void InitMusic();
	// エフェクト生成
	// tips ... Update関数内で呼び出します
	void CreateEffect();	
	// 敵生成
	// arg... delta_time(前フレームからの経過時間)
	// tips1 ... Update関数内で呼び出します
	// tips2 ... stage3のみで使用します
	void CreateEnemy(float delta_time);							
	// ボスのエフェクトとの当たり判定
	// tips1 ... CollisionCheck関数内で呼び出します
	// tips2 ... stageBossのみで使用します
	void CollisionCheckBoss();
	// プレイヤーと敵の通常当たり判定
	// tips1 ... Update関数内で呼び出します
	void CollisionCheck(float delta_time);						
	// 敵の削除とメモリ解放
	// tips ... Finalize関数内で呼び出します
	void RemoveAndDelete();		

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};