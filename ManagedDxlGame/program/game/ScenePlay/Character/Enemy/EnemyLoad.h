#pragma once
#include "../../../../engine/GameEngine.h"
#include "../../Map/Map.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// 敵の情報を読み込むクラス
//
/////////////////////////////////////////////////////////////////////////////////////////


class EnemyLoad
{

private:

	//-----------------------------------メンバ変数-----------------------------------//

	// マップのポインタ
	Map* m_map = nullptr;

	//-------------------------------------------------------------------------------//


	//-----------------------------------メンバ関数-----------------------------------//

public:

	// 敵情報の読み込み
	// arg ... CSVファイルのパス
	// tips1 ... ScenePlayの初期化関数で一度だけ呼び出す
	// tips2 ... 敵IDと敵の情報（struct）を対応させるための関数です
	// ex ... LoadEnemyInfo("csv/EnemyLoad.csv")
    std::map<int, sEnemyInfo> LoadEnemyInfo(const std::string& csvPath);            
	// 敵のマップ内座標データの読み込み
	// arg ... CSVファイルのパス
	// tips ... ScenePlayの初期化関数で一度だけ呼び出す
	// ex ... LoadEnemyData("csv/EnemyPos.csv")
	std::list<sEnemyPosData> LoadEnemyData(const std::string& csvPath);				
};
