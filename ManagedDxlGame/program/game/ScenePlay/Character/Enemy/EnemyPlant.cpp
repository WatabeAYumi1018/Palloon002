#include "../../Camera/Camera.h"
#include "EnemyPlant.h"
#include "../Player/Player.h"

EnemyPlant::EnemyPlant
(
    const sEnemyPosData& data
    , const sEnemyInfo& info
    , Player* player
    , Map*map,Collision *collision
    , Camera* camera
) 
    :Enemy(data, info, player, map, collision, camera)
{
    m_is_direction_right = false;
}

EnemyPlant::~EnemyPlant()
{

}

void EnemyPlant::Update(float delta_time)
{
    //重力で下に落ちる
    m_pos.y += m_gravity.y * delta_time*0.1;

    if (m_player)
    {
        tnl_sequence_.update(delta_time);
    }
}

void EnemyPlant::Draw(float delta_time, const Camera* camera)
{
    if (m_is_active)
    {
        //カメラの位置に合わせて描画位置をずらす
        tnl::Vector3 draw_pos 
            = m_pos - camera->GetTarget() 
            + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

        m_animLoader->Draw(delta_time, draw_pos);
    }
}

bool EnemyPlant::SeqIdle(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    float distance_y = m_pos.y - m_player->GetPos().y;

    if (std::abs(distance_x) < 200 && std::abs(distance_y) < 200)
    {
        tnl_sequence_.change(&EnemyPlant::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        if (m_is_direction_right)
        {
            m_animLoader->SetAnimation(24);
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        if (!m_is_direction_right)
        {
            m_animLoader->SetAnimation(25);
        }
    });

    TNL_SEQ_CO_END;
}

bool EnemyPlant::SeqAttack(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (CanMoveRight() && distance_x < 0)
        {
            m_animLoader->SetAnimation(26);

            m_is_direction_right = true;
        } 
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (CanMoveLeft() && distance_x > 0)
        {
            m_animLoader->SetAnimation(27);

            m_is_direction_right = false;
        }
    });

    tnl_sequence_.change(&EnemyPlant::SeqIdle);

    TNL_SEQ_CO_END;
}
