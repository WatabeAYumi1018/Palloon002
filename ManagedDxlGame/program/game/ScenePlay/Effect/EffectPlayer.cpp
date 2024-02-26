#include "../Character/Player/Player.h"
#include "../Camera/Camera.h"
#include "EffectPlayer.h"

EffectPlayer::EffectPlayer(Player *player, eEffectPlayerType effectType)
	:Effect(tnl::Vector3(0, 0, 0), player)
	, m_effectType(effectType), m_player(player)
{
	
}

EffectPlayer::~EffectPlayer()
{

}

void EffectPlayer::Update(float delta_time)
{
	if (m_is_active) 
	{
		// �G�t�F�N�g�̈ʒu���v���C���[�̈ʒu�ɍX�V
		m_pos = m_player->GetPos();

		EffectHandle();

		m_elapsed_time += delta_time;

		if (m_elapsed_time > m_active_time) 
		{
			m_elapsed_time = 0.0f;

			m_is_active = false;

			return;
		}
	}
}

void EffectPlayer::Draw(float delta_time, const Camera* camera)
{
	if (m_is_active)
	{
		tnl::Vector3 draw_pos;

		if (m_player->GetIsDirectionRight())
		{
			draw_pos 
				=m_pos + m_offset - camera->GetTarget() 
				+ tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		}
		else
		{
			draw_pos 
				=m_pos - m_offset - camera->GetTarget() 
				+tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);
		}

		m_animLoader->Draw(delta_time * 2, draw_pos);
	}
}

//�����蔻��̌v�Z����
void EffectPlayer::CalculateCollisionCircles()
{
	m_collision_circles_pos.clear();

	tnl::Vector3 circle_pos;

	if (m_effectType == eEffectPlayerType::Fire)
	{
		//���ˏ�ɓ����蔻��̉~��z�u
		if (m_player->GetIsDirectionRight())
		{
			//���F�P�̉~
			circle_pos = m_pos;
			m_collision_circles_pos.emplace_back(circle_pos);

			//�����F�Q�̉~
			for (int i = 1; i <= 2; i++)
			{
				circle_pos = m_pos + tnl::Vector3(i * m_size, 0, 0);

				m_collision_circles_pos.emplace_back(circle_pos);
			}

			//�E�F�R�̉~
			for (int i = 1; i <= 3; i++)
			{
				circle_pos = m_pos + tnl::Vector3((i + 2) * m_size, 0, 0);

				m_collision_circles_pos.emplace_back(circle_pos);
			}
		}
		else
		{
			//�F�E�P�̉~
			circle_pos = -m_pos;

			m_collision_circles_pos.emplace_back(circle_pos);

			//�����F�Q�̉~
			for (int i = 1; i <= 2; i++)
			{
				circle_pos = m_pos - tnl::Vector3(i * m_size, 0, 0);

				m_collision_circles_pos.emplace_back(circle_pos);
			}

			//���F�R�̉~
			for (int i = 1; i <= 3; i++)
			{
				circle_pos = m_pos - tnl::Vector3((i + 2) * m_size, 0, 0);

				m_collision_circles_pos.emplace_back(circle_pos);
			}
		}
	}

	else if (m_effectType == eEffectPlayerType::Beam)
	{
		//������ɓ����蔻��̉~��z�u
		for (int i = 0; i < 10; i++)
		{
			if (m_player->GetIsDirectionRight())
			{
				circle_pos = m_pos + tnl::Vector3(i * m_size * 2, 0, 0);

				m_collision_circles_pos.emplace_back(circle_pos);
			}
			else
			{
				circle_pos = m_pos - tnl::Vector3(i * m_size * 2, 0, 0);

				m_collision_circles_pos.emplace_back(circle_pos);
			}		
		}
	}
}

//�t�@�C�A�̃A�j���[�V�����ݒ�
void EffectPlayer::EffectFireHandle()
{
	if (m_player->GetIsDirectionRight())
	{
		m_animLoader->SetAnimation(56);  
	}
	else
	{
		m_animLoader->SetAnimation(57); 
	}
}

//�r�[���̃A�j���[�V�����ݒ�
void EffectPlayer::EffectBeamHandle()
{
	if (m_player->GetIsDirectionRight())
	{
		m_animLoader->SetAnimation(58);  
	}
	else
	{
		m_animLoader->SetAnimation(59);  
	}
}

//�G�t�F�N�g�̃A�j���[�V�����ݒ�
void EffectPlayer::EffectHandle()
{
	if (m_effectType == eEffectPlayerType::Fire)
	{
		EffectFireHandle();
	}
	
	else if (m_effectType == eEffectPlayerType::Beam)
	{
		EffectBeamHandle();
	}
}