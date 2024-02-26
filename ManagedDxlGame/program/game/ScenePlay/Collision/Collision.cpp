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

// �}�b�v�`�b�v�Ƃ̓����蔻����s������
// �L�����N�^�[���O���b�h���W�ɕϊ�
tnl::Vector3 Collision
::GetCharacterMapChipPos(const tnl::Vector3& charaPos, const Map* map)
{
    //�L�����̈ʒu����O���b�h���W���擾
    float chip_x = charaPos.x / map->MAP_CHIP_SIZE;

    float chip_y = charaPos.y / map->MAP_CHIP_SIZE;

    return tnl::Vector3(chip_x, chip_y, 0.0f);
}

//�����蔻��̎擾�Ɗi�[
std::vector<sCollisionInfo> Collision
::GetRowChips(int chip_x, int i, int range, const Map* map)
{
    //�����蔻������i�[����z��
    std::vector<sCollisionInfo> rowChips;

    //�L�����̍��W������͂̃}�b�v�`�b�v���擾
    for (int j = chip_x - range; j <= chip_x + range; ++j)
    {
        //�͈͊O�͖���
        if (j < 0 || j >= map->GetCollisionInfo()[i].size())
        {
            continue;
        }

        //�͈͓��̓����蔻������擾
        sCollisionInfo info = map->GetCollisionInfo()[i][j];

        //�����蔻�肪�Ȃ��ꍇ�͖���
        if (info.s_type != eMapCollisionType::None)
        {
            rowChips.emplace_back(info);
        }
    }
    return rowChips;
}

//�����蔻��̗L�����m�F
bool Collision
::IsRowCollisionExists(const std::vector<sCollisionInfo>& rowChips)
{
    //�L��̏ꍇ�̂ݐ�ɐi��
    return !rowChips.empty();
}

// �L�����N�^�[�̎��͂̃}�b�v�`�b�v���擾����(�����蔻�菈���y���̂���)
// ��ʓI�ɃL�����𒆐S��(2*range+1)*(2*range+1)�͈̔͂̃}�b�v�`�b�v���擾
std::vector<std::vector<sCollisionInfo>> Collision
::GetSurroundingChips(Character* chara, Map* map, int range)
{
    tnl::Vector3 current_pos = chara->GetPos();
   
    // ���݂̍��W����O�̍��W������
    // �}�b�v�`�b�v�̃T�C�Y��菬�����ꍇ�̓L���b�V����Ԃ�
    // �L���b�V����Ԃ����ƂŁA�����蔻��̏������y������
    if ((current_pos - m_last_chara_pos).length() < map->MAP_CHIP_SIZE)
    {
        return m_cached_chips;
    }

    std::vector<std::vector<sCollisionInfo>> chips;

    //�L�����̍��W����O���b�h���W���擾
    tnl::Vector3 chip_pos = GetCharacterMapChipPos(current_pos, map);

    for (int i = chip_pos.y - range; i <= chip_pos.y + range; ++i)
    {
        //�͈͊O�͖���
        if (i < 0 || i >= map->GetCollisionInfo().size())
        {
            continue;
        }

        auto rowChips = GetRowChips(chip_pos.x, i, range, map);

        //�����蔻��̂�����̂̂݊i�[
        if (IsRowCollisionExists(rowChips))
        {
            chips.emplace_back(rowChips);
        }
    }
    //�L���b�V�����X�V
    m_cached_chips = chips;

    m_last_chara_pos = current_pos;

    return chips;
}

//��`�Ƃ̓����蔻��
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
            //��`�ȊO�͖���
            if 
            (
                info.s_type == eMapCollisionType::None 
                || info.s_type == eMapCollisionType::Line 
                ||info.s_type == eMapCollisionType::Clear
            )
            {
                continue;
            }

            //��ԋ߂��_���擾
            tnl::Vector3 nearly_point
                = tnl::GetNearestRectPoint
                   (
                       info.s_pos, info.s_size
                       , info.s_size
                       , chara->GetPos()
                   );

            //��ԋ߂��_�Ƃ̋������L�����T�C�Y��菬�����ꍇ�A�ʒu��␳
            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                //�P�ʃx�N�g�����擾
                tnl::Vector3 normalize 
                    = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                //�ʒu�␳
                chara->SetPos(nearly_point + normalize * chara->GetSize());
            }
        }
    }
}

//�����Ƃ̓����蔻��
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
            //�����ȊO�͖���
            if 
                (
                    info.s_type == eMapCollisionType::None 
                    || info.s_type == eMapCollisionType::Box 
                    ||info.s_type == eMapCollisionType::Clear
                )
            {
                continue;
            }

            //��ԋ߂��_���擾
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

            //��ԋ߂��_�Ƃ̋������L�����T�C�Y��菬�����ꍇ�A�ʒu��␳
            if ((nearly_point - chara->GetPos()).length() < chara->GetSize())
            {
                //�P�ʃx�N�g�����擾
                tnl::Vector3 normalize 
                    = tnl::Vector3::Normalize(chara->GetPos() - nearly_point);
                //�ʒu�␳
                chara->SetPos(nearly_point + normalize * chara->GetSize());
            }
        }
    }
}

//�����蔻��ɉ����ĕ��򏈗�
void Collision::CollisionCalculate(Character* chara, Map* map, int range)
{
    //�L�����̎��Ӎ��W���擾   
    auto surrounding_chips = GetSurroundingChips(chara, map, range);

    for (const auto& row : surrounding_chips) 
    {
        for (const auto& info : row) 
        {
            //Clear�̏ꍇ
            if (info.s_type == eMapCollisionType::Clear) 
            {
                //���W��ݒ�
                m_clear_pos = info.s_pos;
                //Clear�t���O�𗧂Ă�
                m_is_clear = true;
                
                break;
            }
        }
    }
    // ��x����Box��Line�̓����蔻����Ăяo��
    CheckBoxCollision(chara, map, surrounding_chips);

    CheckLineCollision(chara, map, surrounding_chips);
}

//�L�����N�^�[���m�̓����蔻��
void Collision::CollisionCharacter(Player* player, Enemy* enemy)
{
    tnl::Vector3 player_pos = player->GetPos();

    float player_size = player->GetSize();

    tnl::Vector3 enemy_pos = enemy->GetPos();

    float enemy_size = enemy->GetSize();

    // 2�̃L�����N�^�[�̏Փ˂��`�F�b�N
    if 
    (
        wta::IsIntersectCircleCircle
        (player_pos
        , player_size
        , enemy_pos
        , enemy_size)
    )
    {
        //���G��ԂłȂ��ꍇ
        if (!player->GetIsInvincible() && !enemy->GetIsInvincible())
        {
            //�v���C���[�̕��������ʒu�ɂ���ꍇ
            if (enemy_pos.y > player_pos.y)
            {
                if (CheckSoundFile() == 0)
                {
                    MusicManager::GetInstance().PlaySE("hit");
                }
                // �G��HP������������
                enemy->DecreaseHP(1);
                //��莞�Ԗ��G��Ԃɂ���
                enemy->MakeInvincible();

                if (enemy->GetHp() <= 0)
                {
                    // HP��0�ȉ��̏ꍇ�A�G�����S�Ƃ���
                    enemy->SetIsDead(true);
                }
                player->SetIsStamp(true);
            }

            //�v���C���[�̃��[����
            else if (player->GetIsRolling())
            {
                MusicManager::GetInstance().PlaySE("hit");
                
                // �G��HP������������
                enemy->DecreaseHP(1);
                //��莞�Ԗ��G��Ԃɂ���
                enemy->MakeInvincible();

                if (enemy->GetHp() <= 0)
                {
                    // HP��0�ȉ��̏ꍇ�A�G�����S�Ƃ���
                    enemy->SetIsDead(true);
                }
			}

            else
            {
                MusicManager::GetInstance().PlaySE("damaged");
                //�v���C���[��HP�����炷
                player->DecreaseHP(1);
                //��莞�Ԗ��G��Ԃɂ���
                player->MakeInvincible();
            }
        }
    }

    if (wta::IsIntersectCircleCircle(player_pos, player_size, m_clear_pos, 32))
    {
        //�N���A�t���O�𗧂Ă�
		m_is_up = true;
	}
}