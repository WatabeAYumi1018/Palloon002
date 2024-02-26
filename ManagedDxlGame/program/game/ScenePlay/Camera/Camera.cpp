#include "Camera.h"
#include "../Character/Player/Player.h"
#include "../Map/Map.h"

void Camera::Update(float delta_time, Player* player, Map* map)
{
	Scroll(player, map);

	MoveRange(player, map);
}

//���w�i�ƃ`�b�v�̃X�N���[���l���߂��邱��
void Camera::Scroll(Player* player, Map* map)
{
	//�v���C���[����ʒ����ɗ�����X�N���[���J�n
	if (!m_is_scroll)
	{
		if
			(
				player->GetPos().x > DXE_WINDOW_WIDTH >> 1
				|| player->GetPos().y > DXE_WINDOW_HEIGHT >> 1
				)
		{
			m_target = player->GetPos();

			m_is_scroll = true;
		}
	}
	else
	{
		//�v���C���[�̍��W���擾���āA�J�����̍��W��x���X�V
		m_target += (player->GetPos() - m_target) * 0.1f;

		//�v���C���[����ʒ�������O�ꂽ��X�N���[���I��
		if
			(
				(player->GetPos().x <= DXE_WINDOW_WIDTH >> 1
					&& player->GetPos().y <= DXE_WINDOW_HEIGHT >> 1)
				)
		{
			m_is_scroll = false;
		}
	}
}

//�v���C���[�̍��W���擾���āA�J�����̍��W���X�V����
void Camera::MoveRange(Player* player, Map* map)
{
	//�X�N���[���J�n���W
	const float halfWidth = DXE_WINDOW_WIDTH >> 1;

	const float halfHeight = DXE_WINDOW_HEIGHT >> 1;
	
	//�J�����̈ړ��͈�
	const float maxX = map->MAP_CHIP_SIZE * map->GetMapChipX() - halfWidth;

	const float maxY = map->MAP_CHIP_SIZE * map->GetMapChipY() - halfHeight;

	//�����A�c���A�ǂ���ɂ��Ή��\�ɂ���
	if (halfWidth < maxX)
	{
		//clamp�֐��Ŕ͈͓��Ɉړ������߂�Bclamp(�l, �ŏ��l, �ő�l)
		m_target.x = std::clamp(m_target.x, halfWidth, maxX);
	}
	else
	{
		//csv�t�@�C���̃T�C�Y��max�ƂȂ�
		m_target.x = maxX;
	}

	m_target.y = std::clamp(m_target.y, halfHeight, maxY);
}
