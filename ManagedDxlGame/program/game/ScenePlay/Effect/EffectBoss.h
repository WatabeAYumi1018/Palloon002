#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../engine/GameEngine.h"
#include "Effect.h"

class Enemy;
class Player;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �{�X�G�t�F�N�g�̃N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class EffectBoss : public Effect
{

public:

    //--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

    EffectBoss(Enemy* enemy,Player* player);

    ~EffectBoss();

    //---------------------------------------------------------------------------------//

private:

    //-----------------------------------�����o�ϐ�-----------------------------------//           

    // �t�@�C�A�{�[���̍��W
    tnl::Vector3 m_fireball_pos;
    // �Ή����˂̈ʒu�␳
    tnl::Vector3 m_offset_flame = {600,-100,0};  
    // �t�@�C�A�{�[���̈ʒu�␳
    tnl::Vector3 m_offset_fireball = { 200,0,0 };       
    // �t�@�C�A�{�[���̔�ԕ���
    tnl::Vector3 m_fireball_dir;                          

    // �Ή����˂ł̓����蔻��ɂ�3�̉~�̍��W
    std::vector<tnl::Vector3> m_collision_circles_pos;      

    // �G�t�F�N�g�̎��
    eEffectBossType e_effectType = eEffectBossType::None;

    // �G�̃|�C���^
    Enemy* m_enemy = nullptr;
    // �v���C���[�̃|�C���^
    Player* m_player = nullptr;

    //---------------------------------------------------------------------------------//


    //-----------------------------------�����o�֐�-----------------------------------//

    // �t�@�C�A�{�[���̏���(�s��̂��ߒ������ł�)
    // tips ... EffectHandle�֐����ŌĂяo���܂�
    void FireballHandle();                                 
    // �Ή����˂̏���
    // tips ... EffectHandle�֐����ŌĂяo���܂�
    void FlameHandle();									   
    // �G�t�F�N�g��������
    // tips ... Update�֐����ŌĂяo���܂�
    void EffectHandle();									

public:

    // �����蔻��p�̉~�̍��W���v�Z
    // tips ... Update�֐����ŌĂяo���܂�
    void CalculateCollisionCircles();					   

    void Update(float delta_time) override;

    void Draw(float delta_time, const Camera* camera) override;

    //---------------------------------------------------------------------------------//


    //----------------------------------Setter&Getter----------------------------------//

    // �����蔻��p�̉~�̍��W���擾
    std::vector<tnl::Vector3> GetCollisionCirclesPos() const
    { 
        return m_collision_circles_pos; 
    }

    //---------------------------------------------------------------------------------//
};

// ��
// �t�@�C�A�[�{�[���Ɋւ��鏈���͒������ł�