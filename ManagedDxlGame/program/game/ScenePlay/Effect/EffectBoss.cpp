#include "EffectBoss.h"
#include "../../SceneAll/Music/MusicManager.h"
#include "../Character/Enemy/Enemy.h"
#include "../Character/Player/Player.h"
#include "../Camera/Camera.h"


EffectBoss::EffectBoss(Enemy* enemy,Player* player)
    :Effect(tnl::Vector3(0, 0, 0), enemy)
    , m_enemy(enemy), m_player(player)
{
   MusicManager::GetInstance()
       .LoadSE("doragonfire", "music/DoragonFire.mp3");
   
   m_pos = m_enemy->GetPos();

   m_size = 100;
}

EffectBoss::~EffectBoss()
{

}

void EffectBoss::Update(float delta_time)
{
    if (m_enemy->GetIsActiveBoss())
    {
        EffectHandle();

        CalculateCollisionCircles();

        m_elapsed_time += delta_time;

        if (m_elapsed_time > m_active_time)
        {
            m_elapsed_time = 0;

            m_enemy->SetIsActiveBoss(false);
        }

        // ファイアボールの座標更新
        if (e_effectType == eEffectBossType::FireBall)
        {
            m_pos += m_fireball_dir * delta_time * 2;
        }
    }
}
void EffectBoss::Draw(float delta_time, const Camera* camera)
{
    if (m_enemy->GetIsActiveBoss())
    {
       m_animLoader->Draw(delta_time, m_pos);
    }
}

void EffectBoss::CalculateCollisionCircles()
{
    m_collision_circles_pos.clear();

    tnl::Vector3 circle_pos;

    const int DRAGON_FIRE_SIZE = 100; 

    if (e_effectType == eEffectBossType::Flame)
    {
        //右：１つの円
        circle_pos = m_pos.x+ DRAGON_FIRE_SIZE;

        m_collision_circles_pos.emplace_back(circle_pos);

        //左：２つの円
        for (int i = 1; i <= 2; i++)
        {
            circle_pos
                = m_pos - tnl::Vector3(i * DRAGON_FIRE_SIZE, 0, 0);

            m_collision_circles_pos.emplace_back(circle_pos);
        }
    }

    else if (e_effectType == eEffectBossType::FireBall)
    {
        m_collision_circles_pos.clear();

        m_collision_circles_pos.emplace_back(m_fireball_pos);
    }
}

void EffectBoss::FlameHandle()
{
    m_pos = m_enemy->GetPos() - m_offset_flame;

    e_effectType = eEffectBossType::Flame;
    
    MusicManager::GetInstance().PlaySE("doragonfire");

    m_animLoader->SetAnimation(63);
}

void EffectBoss::FireballHandle()
{
    e_effectType = eEffectBossType::FireBall;
       
    m_animLoader->SetAnimation(64);

    m_pos = m_enemy->GetPos() - m_offset_fireball;

    m_fireball_dir = m_player->GetPos() - m_pos;

    //ベクトルの正規化
    float length 
        =std::sqrt
        (
            m_fireball_dir.x * m_fireball_dir.x 
            + m_fireball_dir.y * m_fireball_dir.y
        );

    if (length != 0)
    {
        m_fireball_dir.x /= length;

        m_fireball_dir.y /= length;
    }
}

void EffectBoss::EffectHandle()
{
    if (m_enemy->GetIsFlame())
    {
        FlameHandle();
    }
    else if (m_enemy->GetIsFireBall())
    {
        FireballHandle();
    }
}