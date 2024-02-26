#include "wta_DrawAnim.h"

namespace wta
{
    DrawAnim::DrawAnim(const std::string& csvPath, const std::string& basePath) 
        :m_current_frame(0), m_elapsed_time(0.0f), m_frame_duration(0.2f)
    {
        m_animations = LoadAnimationData(csvPath, basePath);
    }

    void DrawAnim::SetAnimation(int id) 
    {
        for (const auto& anim : m_animations)
        {
            if (anim.s_id == id)
            {
                // アニメーションの種類が変わった場合は初期化
                if (m_currentAnim != &anim)
                {
                    m_elapsed_time = 0.0f;

                    m_current_frame = 0;
                }

                m_currentAnim = &anim;

                return;
            }
        }
        // 見つからなかった場合はnullptrを設定
        m_currentAnim = nullptr;  
    }

    // アニメーションを描画
    void DrawAnim::Draw
    (
        float delta_time
        , tnl::Vector3 pos
        , float scale
        , float angle
    ) 
    {
        // 現在のアニメーションがない、空の場合何もしない
        if (!m_currentAnim || m_currentAnim->s_anim_hdl.empty())
        {
            return;
        }
       
        m_elapsed_time += delta_time;
        
        if (m_elapsed_time >= m_frame_duration) 
        {
            m_elapsed_time -= m_frame_duration;

            ++m_current_frame;
           
            if (m_currentAnim->s_loop) 
            {
                m_current_frame %= m_currentAnim->s_anim_hdl.size();
            }
            // ループしない場合最初のフレームにリセット
            else if (m_current_frame >= m_currentAnim->s_anim_hdl.size())
            {
                m_current_frame = 0;  
            }
        }

        DrawRotaGraph
        (
            static_cast<int>(pos.x)
            , static_cast<int>(pos.y)
            , scale
            , tnl::ToRadian(angle)
            , m_currentAnim->s_anim_hdl[m_current_frame]
            , TRUE
        );
    }
}
