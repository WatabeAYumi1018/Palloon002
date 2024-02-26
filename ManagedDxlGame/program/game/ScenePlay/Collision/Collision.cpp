#include "../../../wta_library/wta_IsIntersectCalc.h"
#include "../../SceneAll/Music/MusicManager.h"
#include "../Character/Character.h"
#include "../Character/Player/Player.h"
#include "../Character/Enemy/Enemy.h"
#include "../Map/Map.h"
#include "Collision.h"

Collision::Collision() : m_last_chara_pos(0, 0, 0)
{
    MusicManager::GetInstance()
        .LoadSE("hit", "music/playerStamp.wav");

    MusicManager::GetInstance()
        .LoadSE("damaged", "music/damaged.wav");
}

// マップチップとの当たり判定を行うため
// キャラクターをグリッド座標に変換
tnl::Vector3 Collision
::GetCharacterMapChipPos(const tnl::Vector3& charaPos, const Map* map)
{
    //キャラの位置からグリッド座標を取得
    float chip_x = charaPos.x / map->MAP_CHIP_SIZE;

    float chip_y = charaPos.y / map->MAP_CHIP_SIZE;

    return tnl::Vector3(chip_x, chip_y, 0.0f);
}

//当たり判定の取得と格納
std::vector<sCollisionInfo> Collision
::GetRowChips(int chip_x, int i, int range, const Map* map)
{
    //当たり判定情報を格納する配列
    std::vector<sCollisionInfo> rowChips;

    //キャラの座標から周囲のマップチップを取得
    for (int j = chip_x - range; j <= chip_x + range; ++j)
    {
        //範囲外は無視
        if (j < 0 || j >= map->GetCollisionInfo()[i].size())
        {
            continue;
        }

        //範囲内の当たり判定情報を取得
        sCollisionInfo info = map->GetCollisionInfo()[i][j];

        //当たり判定がない場合は無視
        if (info.s_type != eMapCollisionType::None)
        {
            rowChips.emplace_back(info);
        }
    }
    return rowChips;
}

//当たり判定の有無を確認
bool Collision
::IsRowCollisionExists(const std::vector<sCollisionInfo>& rowChips)
{
    //有りの場合のみ先に進む
    return !rowChips.empty();
}

// キャラクターの周囲のマップチップを取得する(当たり判定処理軽減のため)
// 一般的にキャラを中心に(2*range+1)*(2*range+1)の範囲のマップチップを取得
std::vector<std::vector<sCollisionInfo>> Collision
::GetSurroundingChips(Character* chara, Map* map, int range)
{
    tnl::Vector3 current_pos = chara->GetPos();
   
    // 現在の座標から前の座標を引く
    // マップチップのサイズより小さい場合はキャッシュを返す
    // キャッシュを返すことで、当たり判定の処理を軽減する
    if ((current_pos - m_last_chara_pos).length() < map->MAP_CHIP_SIZE)
    {
        return m_cached_chips;
    }

    std::vector<std::vector<sCollisionInfo>> chips;

    //キャラの座標からグリッド座標を取得
    tnl::Vector3 chip_pos = GetCharacterMapChipPos(current_pos, map);

    for (int i = chip_pos.y - range; i <= chip_pos.y + range; ++i)
    {
        //範囲外は無視
        if (i < 0 || i >= map->GetCollisionInfo().size())
        {
            continue;
        }

        auto rowChips = GetRowChips(chip_pos.x, i, range, map);

        //当たり判定のあるもののみ格納
        if (IsRowCollisionExists(rowChips))
        {
            chips.emplace_back(rowChips);
        }
    }
    //キャッシュを更新
    m_cached_chips = chips;

    m_last_chara_pos = current_pos;

    return chips;
}

//矩形との当たり判定
void Collision::CheckBoxCollision
(
    Character* chara
    , Map* map
    , const std::vector<std::vector<sCollisionInfo>>& surroundingChips
)
{
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            //矩形以外は無視
            if 
            (
                info.s_type == eMapCollisionType::None 
                || info.s_type == eMapCollisionType::Line 
                ||info.s_type == eMapCollisionType::Clear
            )
            {
                continue;
            }

            //一番近い点を取得
            tnl::Vector3 nearly_point
                = tnl::GetNearestRectPoint
                   (
                       info.s_pos, info.s_size
                       , info.s_size
                       , chara->GetPos()
                   );

            //一番近い点との距離がキャラサイズより小さい場合、位置を補正
            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                //単位ベクトルを取得
                tnl::Vector3 normalize 
                    = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                //位置補正
                chara->SetPos(nearly_point + normalize * chara->GetSize());
            }
        }
    }
}

//線分との当たり判定
void Collision::CheckLineCollision
(
    Character* chara
    , Map* map
    , const std::vector<std::vector<sCollisionInfo>>& surroundingChips
)
{
    for (const auto& row : surroundingChips)
    {
        for (const auto& info : row)
        {
            //線分以外は無視
            if 
                (
                    info.s_type == eMapCollisionType::None 
                    || info.s_type == eMapCollisionType::Box 
                    ||info.s_type == eMapCollisionType::Clear
                )
            {
                continue;
            }

            //一番近い点を取得
            tnl::Vector3 nearly_point
                =tnl::GetNearestPointLine
                 (
                     chara->GetPos()
                      ,{info.s_pos.x - (info.s_size >> 1)
                        ,info.s_pos.y + (info.s_size >> 1)
                        ,0 }
                      ,{info.s_pos.x + (info.s_size >> 1)
                        ,info.s_pos.y - (info.s_size >> 1)
                        ,0 }
                  );

            //一番近い点との距離がキャラサイズより小さい場合、位置を補正
            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                //単位ベクトルを取得
                tnl::Vector3 normalize 
                    = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                //位置補正
                chara->SetPos(nearly_point + normalize * chara->GetSize());
            }
        }
    }
}

//当たり判定に応じて分岐処理
void Collision::CollisionCalculate(Character* chara, Map* map, int range)
{
    //キャラの周辺座標を取得   
    auto surrounding_chips = GetSurroundingChips(chara, map, range);

    for (const auto& row : surrounding_chips) 
    {
        for (const auto& info : row) 
        {
            //Clearの場合
            if (info.s_type == eMapCollisionType::Clear) 
            {
                //座標を設定
                m_clear_pos = info.s_pos;
                //Clearフラグを立てる
                m_is_clear = true;
                
                break;
            }
        }
    }
    // 一度だけBoxとLineの当たり判定を呼び出す
    CheckBoxCollision(chara, map, surrounding_chips);

    CheckLineCollision(chara, map, surrounding_chips);
}

//キャラクター同士の当たり判定
void Collision::CollisionCharacter(Player* player, Enemy* enemy)
{
    tnl::Vector3 player_pos = player->GetPos();

    float player_size = player->GetSize();

    tnl::Vector3 enemy_pos = enemy->GetPos();

    float enemy_size = enemy->GetSize();

    // 2つのキャラクターの衝突をチェック
    if 
    (
        wta::IsIntersectCircleCircle
        (player_pos
        , player_size
        , enemy_pos
        , enemy_size)
    )
    {
        //無敵状態でない場合
        if (!player->GetIsInvincible() && !enemy->GetIsInvincible())
        {
            //プレイヤーの方が高い位置にいる場合
            if (enemy_pos.y > player_pos.y)
            {
                if (CheckSoundFile() == 0)
                {
                    MusicManager::GetInstance().PlaySE("hit");
                }
                // 敵のHPを減少させる
                enemy->DecreaseHP(1);
                //一定時間無敵状態にする
                enemy->MakeInvincible();

                if (enemy->GetHp() <= 0)
                {
                    // HPが0以下の場合、敵を死亡とする
                    enemy->SetIsDead(true);
                }
                player->SetIsStamp(true);
            }

            //プレイヤーのロール中
            else if (player->GetIsRolling())
            {
                MusicManager::GetInstance().PlaySE("hit");
                
                // 敵のHPを減少させる
                enemy->DecreaseHP(1);
                //一定時間無敵状態にする
                enemy->MakeInvincible();

                if (enemy->GetHp() <= 0)
                {
                    // HPが0以下の場合、敵を死亡とする
                    enemy->SetIsDead(true);
                }
			}

            else
            {
                MusicManager::GetInstance().PlaySE("damaged");
                //プレイヤーのHPを減らす
                player->DecreaseHP(1);
                //一定時間無敵状態にする
                player->MakeInvincible();
            }
        }
    }

    if (wta::IsIntersectCircleCircle(player_pos, player_size, m_clear_pos, 32))
    {
        //クリアフラグを立てる
		m_is_up = true;
	}
}