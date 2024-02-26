#include "../../Camera/Camera.h"
#include "EnemyFairy.h"
#include "../Player/Player.h"

EnemyFairy::EnemyFairy
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

}

EnemyFairy::~EnemyFairy()
{

}

void EnemyFairy::Update(float delta_time)
{
    if (m_player)
    {
        tnl_sequence_.update(delta_time);
    }

    Invincible(delta_time);
}

void EnemyFairy::Draw(float delta_time, const Camera* camera)
{
    //カメラの位置に合わせて描画位置をずらす
    tnl::Vector3 draw_pos 
        = m_pos - camera->GetTarget() 
        + tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

    //無敵中は点滅描画
    if (m_is_invincible)
    {
        // 0.1秒ごとに表示・非表示を切り替えて点滅
        if (static_cast<int>(m_invincible_time * 10) % 2 == 0)
        {
            m_animLoader->Draw(delta_time, draw_pos);
        }
    }
    else
    {
        m_animLoader->Draw(delta_time, draw_pos);
    }
}

void EnemyFairy::RandomType()
{
    int random_type = rand() % 3 ;

    switch (random_type)
    {  

    case 0:
        
        s_type = Peach;
    
        break;
    
    case 1:
    
        s_type = Blue;
        
        break;
    
    case 2:
    
        s_type = Yellow;
        
        break;
    }
}

bool EnemyFairy::SeqIdle(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    float distance_y = m_pos.y - m_player->GetPos().y;

    if (std::abs(distance_x) < 200 && std::abs(distance_y) < 200)
    {
        tnl_sequence_.change(&EnemyFairy::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        if (m_is_direction_right)
        {
            if (s_type == Peach)
            {
                m_animLoader->SetAnimation(34);
            }
            else if (s_type == Blue)
            {
				m_animLoader->SetAnimation(40);
			}
            else if (s_type == Yellow)
            {
				m_animLoader->SetAnimation(48);
			}
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        if (!m_is_direction_right)
        {
            if (s_type == Peach)
            {
                m_animLoader->SetAnimation(35);
            }
            else if (s_type == Blue)
            {
                m_animLoader->SetAnimation(41);
            }
            else if (s_type == Yellow)
            {
                m_animLoader->SetAnimation(47);
            }
        }
    });

    tnl_sequence_.change(&EnemyFairy::SeqMove);
    
    TNL_SEQ_CO_END;
}

bool EnemyFairy::SeqMove(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    float distance_y = m_pos.y - m_player->GetPos().y;

    if (std::abs(distance_x) < 200 && std::abs(distance_y) < 200)
    {
        tnl_sequence_.change(&EnemyFairy::SeqAttack);
    }

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        if (s_type == Peach)
        {
            m_animLoader->SetAnimation(36);
        }
        else if (s_type == Blue)
        {
            m_animLoader->SetAnimation(42);
        }
        else if (s_type == Yellow)
        {
            m_animLoader->SetAnimation(48);
        }
        m_pos.x += m_velocity.x * delta_time;
        m_is_direction_right = true;
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(2, delta_time, [&]()
    {
        if (s_type == Peach)
        {
            m_animLoader->SetAnimation(37);
        }
        else if (s_type == Blue)
        {
            m_animLoader->SetAnimation(43);
        }
        else if (s_type == Yellow)
        {
            m_animLoader->SetAnimation(49);
        }
        m_pos.x -= m_velocity.x * delta_time;
        m_is_direction_right = false;        
    });

    tnl_sequence_.change(&EnemyFairy::SeqIdle);

    TNL_SEQ_CO_END;
}
bool EnemyFairy::SeqAttack(float delta_time)
{
    float distance_x = m_pos.x - m_player->GetPos().x;

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (distance_x < 0)
        {
            if (s_type == Peach)
            {
                m_animLoader->SetAnimation(38);
            }
            else if (s_type == Blue)
            {
                m_animLoader->SetAnimation(44);
            }
            else if (s_type == Yellow)
            {
                m_animLoader->SetAnimation(50);
            }
            m_pos.x += m_velocity.x * delta_time;

            m_is_direction_right = true;
        }
    });

    TNL_SEQ_CO_TIM_YIELD_RETURN(1, delta_time, [&]()
    {
        if (distance_x > 0)
        {
            if (s_type == Peach)
            {
                m_animLoader->SetAnimation(39);
            }
            else if (s_type == Blue)
            {
                m_animLoader->SetAnimation(45);
            }
            else if (s_type == Yellow)
            {
                m_animLoader->SetAnimation(51);
            }

            m_pos.x -= m_velocity.x * delta_time;

            m_is_direction_right = false;
        }
    });

    tnl_sequence_.change(&EnemyFairy::SeqMove);

    TNL_SEQ_CO_END;
}
