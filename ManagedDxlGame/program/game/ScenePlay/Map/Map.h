#pragma once
#include "../../../engine/GameEngine.h"

class Camera;
class Player;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// csvからのマップチップ、当たり判定の読み取り
//
/////////////////////////////////////////////////////////////////////////////////////////


class Map final	
{

private:

	//-----------------------------------struct構造-----------------------------------//

	struct sStageInfo
	{
		// ステージ名
		std::string s_stage_name;
		// 背景画像のパス
		std::string s_background_hdl;
		// マップチップのパス
		std::string s_map_csv;
		// 当たり判定のパス
		std::string s_collision_csv;
		// 敵のパス
		std::string s_enemy_csv;
		// BGMのパス
		std::string s_music_bgm;
		// プレイヤーの初期座標
		tnl::Vector3 s_initial_player_pos;
	};

	//--------------------------------------------------------------------------------//

public:

	//--------------------------コンストラクタ、デストラクタ--------------------------//

	explicit Map(const std::string& stageName);

	virtual ~Map();

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ変数-----------------------------------//
	
	// 横幅
	static const int MAP_ROW_COL = 7;			
	// 縦幅
	static const int MAP_ALL_NUM = 49;			
	// マップチップのサイズ
	static const int MAP_CHIP_SIZE = 32;		

private:

	// マップチップのハンドル
	int m_map_hdl[MAP_ALL_NUM];									
	
	// マップチップの座標
	tnl::Vector3 m_pos;											
	
	// マップチップの描画情報
	std::vector<std::vector<int>> m_csv_map_tile;				
	// マップチップの当たり判定描画情報
	std::vector<std::vector<int>> m_csv_collision;				
	// マップチップの当たり判定情報
	std::vector<std::vector<sCollisionInfo>> m_collision_info;	
	// 各ステージの情報
	std::vector<sStageInfo> m_stageList =						
	{ 
		{
			"stage1"
			,"graphics/stage1-1.jpg"
			,"csv/stage1-1.csv"
			,"csv/stage1-1collision.csv"
			,"csv/stage1-1enemy.csv"
			,"music/stage1-1.mp3"
			,{0,100,0}
		},

		{
			"stage2"
			,"graphics/stage1-2.png"
			,"csv/stage1-2.csv"
			,"csv/stage1-2collision.csv"
			,"csv/stage1-2enemy.csv"
			,"music/stage1-2.mp3"
			,{0,5800,0}
		},
		
		{
			"stage3"
			,"graphics/stage1-3.png"
			,"csv/stage1-3.csv"
			,"csv/stage1-3collision.csv"
			,"csv/stage1-3enemy.csv"
			,"music/stage1-3.mp3"
			,{100,300,0}
		},

		{
			"stageBoss"
			,"graphics/stageBoss.png"
			,"csv/stageBOSS.csv"
			,"csv/stageBOSScollision.csv"
			,"csv/stageBOSSenemy.csv"
			,"music/stageBoss.mp3"
			,{0,300,0}
		}
	};																						

	// 現在のステージ情報
	sStageInfo s_current_stage_info;							

public:

	//--------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

	// 当たり判定専用のマップ関数
	// tips1 ... カメラ移動による更新が必要な処理です
	// tips2 ... ScenePlayクラスのUpdate関数内で呼び出します
	void LoadMapCollision();									
	
	void Initialize(const std::string& stageName);

	void Draw(const Camera* camera);

	void Finalize();

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// マップチップの横幅を取得
	const size_t GetMapChipX() const { return m_csv_map_tile[0].size(); }

	// マップチップの縦幅を取得
	const size_t GetMapChipY() const { return m_csv_map_tile.size(); }
	
	// 当たり判定情報を取得
	const std::vector<std::vector<sCollisionInfo>>& GetCollisionInfo() const 
	{
		return m_collision_info; 
	}
	
	// 現在のステージ情報を取得
	const sStageInfo& GetCurrentStageInfo() const 
	{
		return s_current_stage_info; 
	}

	// ステージ情報を取得
	const std::vector<sStageInfo> GetStageList() const { return m_stageList; }

	//--------------------------------------------------------------------------------//
};