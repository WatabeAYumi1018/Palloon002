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
                // �A�j���[�V�����̎�ނ��ς�����ꍇ�͏�����
                if (m_currentAnim != &anim)
                {
                    m_elapsed_time = 0.0f;

                    m_current_frame = 0;
                }

                m_currentAnim = &anim;

                return;
            }
        }
        // ������Ȃ������ꍇ��nullptr��ݒ�
        m_currentAnim = nullptr;  
    }

    // �A�j���[�V������`��
    void DrawAnim::Draw
    (
        float delta_time
        , tnl::Vector3 pos
        , float scale
        , float angle
    ) 
    {
        // ���݂̃A�j���[�V�������Ȃ��A��̏ꍇ�������Ȃ�
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
            // ���[�v���Ȃ��ꍇ�ŏ��̃t���[���Ƀ��Z�b�g
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
