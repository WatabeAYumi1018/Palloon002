#include "../../../../library/tnl_csv.h"
#include "EnemyLoad.h"
#include "../../Camera/Camera.h"
#include "../../Map/Map.h"
#include "Enemy.h"


std::map<int, sEnemyInfo> 
    EnemyLoad::LoadEnemyInfo(const std::string& file_path)
{
    std::map<int, sEnemyInfo> enemyInfo;

    // �G�̃p�����[�^�[�Ȃǂ�CSV����ǂݍ���
    auto data = tnl::LoadCsv(file_path);

    // �ŏ���0�s�ڂ͓ǂݎ��s�v�̂��ߍ폜
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

    // CSV��ǂݎ��
    auto csvData = tnl::LoadCsv(file_path);

    // �񎟌��z������[�v�ŉ�
    for (int i = 0; i < csvData.size(); ++i)
    {
        for (int j = 0; j < csvData[i].size(); ++j)
        {
            // -1�ł͂Ȃ��ꍇ�A�G�f�[�^�Ƃ��ĕۑ�
            if (csvData[i][j].getInt() != -1)
            {
                sEnemyPosData data;

                //�����蔻��̒��S���W���v�Z
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
