#include <random>
#include "Enemy.h"
#include "../../Map/Map.h"
#include "../../Collision/Collision.h"
#include "../../Camera/Camera.h"
#include "../Player/Player.h"
#include "../../Camera/Camera.h"

Enemy::Enemy
(
    const sEnemyPosData& data
    , const sEnemyInfo& info
    ,Player* player
    , Map* map
    , Collision* collision
    , Camera* camera
)
    : Character
    (
        data.s_pos
        , info.s_size
        , info.s_hp
        , tnl::Vector3(100, 0, 0)
    )
    ,m_player(player)
    , m_map(map)
    , m_collision(collision)
    ,m_camera(camera)
{
    m_type_id = info.s_id;

    m_type = info.s_name;

    m_color = info.s_color;

    //元データ保存
    s_date = data;
}

float Enemy::DistanceCalc()
{
    float distance = std::sqrt
    (
        //powは2乗（三平方の定理）
        std::pow(m_pos.x - m_player->GetPos().x, 2) 
        +std::pow(m_pos.y - m_player->GetPos().y, 2)
    );
    return distance;
}

//矩形ならば進行可能とする
bool Enemy::CanMoveRight()
{
    if (m_is_dead)
    {
        return false;
    }

    tnl::Vector3 forward_pos = m_pos + tnl::Vector3(32, 40, 0);

    tnl::Vector3 chip_pos 
        = m_collision->GetCharacterMapChipPos(forward_pos, m_map);

    sCollisionInfo forward_collision 
        = m_map->GetCollisionInfo()[chip_pos.y][chip_pos.x];

    return forward_collision.s_type == eMapCollisionType::Box;
}

bool Enemy::CanMoveLeft()
{
    if (m_is_dead)
    {
        return false;
    }

    tnl::Vector3 backward_pos = m_pos - tnl::Vector3(32, -40, 0);

    tnl::Vector3 chip_pos 
        = m_collision->GetCharacterMapChipPos(backward_pos, m_map);

    sCollisionInfo backward_collision
        = m_map->GetCollisionInfo()[chip_pos.y][chip_pos.x];
    
    return backward_collision.s_type == eMapCollisionType::Box;
}


