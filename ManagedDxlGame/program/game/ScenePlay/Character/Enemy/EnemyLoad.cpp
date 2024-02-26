#include "../../../../library/tnl_csv.h"
#include "EnemyLoad.h"
#include "../../Camera/Camera.h"
#include "../../Map/Map.h"
#include "Enemy.h"


std::map<int, sEnemyInfo> 
    EnemyLoad::LoadEnemyInfo(const std::string& file_path)
{
    std::map<int, sEnemyInfo> enemyInfo;

    // 敵のパラメーターなどをCSVから読み込む
    auto data = tnl::LoadCsv(file_path);

    // 最初の0行目は読み取り不要のため削除
    if (!data.empty())
    {
        data.erase(data.begin());
    }

    for (const auto& row : data)
    {
        sEnemyInfo info;

        info.s_id = row[0].getInt();

        info.s_name = row[1].getString();

        info.s_color = row[2].getString();

        info.s_hp = row[3].getInt();

        info.s_size = row[4].getInt();

        enemyInfo[info.s_id] = info;
    }
    return enemyInfo;
}

std::list<sEnemyPosData> 
    EnemyLoad::LoadEnemyData(const std::string& file_path)
{
    std::list<sEnemyPosData> enemyData;

    // CSVを読み取る
    auto csvData = tnl::LoadCsv(file_path);

    // 二次元配列をループで回す
    for (int i = 0; i < csvData.size(); ++i)
    {
        for (int j = 0; j < csvData[i].size(); ++j)
        {
            // -1ではない場合、敵データとして保存
            if (csvData[i][j].getInt() != -1)
            {
                sEnemyPosData data;

                //当たり判定の中心座標を計算
                float posX = static_cast<int>(j * m_map->MAP_CHIP_SIZE);

                float posY = static_cast<int>(i * m_map->MAP_CHIP_SIZE);

                data.s_pos = tnl::Vector3(posX, posY, 0);
                
                data.s_type_id = csvData[i][j].getInt();
                
                enemyData.emplace_back(data);
            }
        }
    }
    return enemyData;
}
