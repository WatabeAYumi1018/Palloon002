#include "../../Camera/Camera.h"
#include "EnemyBird.h"
#include "../Player/Player.h"

EnemyBird::EnemyBird
(
    const sEnemyPosData& data
    , const sEnemyInfo& info
    , Player* player
    , Map* map
    , Collision* collision
    , Camera* camera
) 
    :Enemy(data, info, player, map, collision, camera)
{
    m_is_direction_right = false;
}

EnemyBird::~EnemyBird()
{
 
}

void EnemyBird::Update(float delta_time)
{
    if (m_player)
    {
        tnl_sequence_.update(delta_time);
    }
}

void EnemyBird::Draw(float delta_time, const Camera* camera)
{
    //ƒJƒƒ‰‚ÌˆÊ’u‚É‡‚í‚¹‚Ä•`‰æˆÊ’u‚ð‚¸‚ç‚·
    tnl::Vector3 draw_pos 
        = m_pos - camera->GetTarget() 
        + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    m_animLoader->Draw(delta_time, draw_pos);
}

bool EnemyBird::SeqMove(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    float distance_y = m_pos.y - m_player->GetPos().y;

    if (std::abs(distance_x) < 200 && std::abs(distance_y) < 100)
    {
        tnl_sequence_.change(&EnemyBird::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        m_animLoader->SetAnimation(52);

        m_pos.x += m_velocity.x * delta_time;

        m_is_direction_right = true;
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        m_animLoader->SetAnimation(53);

        m_pos.x -= m_velocity.x * delta_time;

        m_is_direction_right = false;

    });

    TNL_SEQ_CO_END;
}

bool EnemyBird::SeqAttack(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (distance_x < 0)
        {
            m_animLoader->SetAnimation(54);

            m_pos.x += m_velocity.x * delta_time * 2.0f;

            m_is_direction_right = true;
        }

    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {

        if (distance_x > 0)
        {
            m_animLoader->SetAnimation(55);

            m_pos.x -= m_velocity.x * delta_time * 2.0f;

            m_is_direction_right = false;
        }
    });

    tnl_sequence_.change(&EnemyBird::SeqMove);

    TNL_SEQ_CO_END;
}
