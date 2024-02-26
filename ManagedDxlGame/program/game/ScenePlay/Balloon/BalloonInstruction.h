#pragma once
#include "../../SceneAll/Balloon/Balloon.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
//��������̕��D�N���X�i�`��ƍX�V�j
//
/////////////////////////////////////////////////////////////////////////////////////////


class BalloonInstruction : public Balloon
{

private:

    //-----------------------------------enum�N���X-----------------------------------//

    // �C���X�g���N�V�����i������@�j�̎��
    enum class eInstructionType
    {
        Run,
        Roll,
        Float,
        Stamp,
        Fire,
        Beam,
        Max
    };

    //--------------------------------------------------------------------------------//

public:

    //--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

    BalloonInstruction();

    ~BalloonInstruction() {}

    //--------------------------------------------------------------------------------//

private:

    //-----------------------------------�����o�ϐ�-----------------------------------//

    // �T�C�Y
    int m_size = 300;
    // �ő�`�掞��
    int m_draw_count_time = 0;

    // �o�ߎ���
    float m_elapsed_time = 0.0f;
    // ���x
    float m_velocity = 0.1f;
    // �U��
    float m_amplitude = 1.0f;

    // �e�I�t�Z�b�g���i�[����z��
    std::vector<float> m_phase_offsets;

    // enum�N���X�̒l���L�[�Ƃ��āA�e�摜�n���h�����i�[����}�b�v
    std::map<eInstructionType, int> m_instruction_hdl;
    // enum�N���X�̒l���L�[�Ƃ��āA�e���W���i�[����}�b�v
    std::map<eInstructionType, tnl::Vector3> m_pos_graphics;

    //--------------------------------------------------------------------------------//

public:

    //-----------------------------------�����o�֐�-----------------------------------//

    void Initialize() override;

    void Update(float delta_time) override;

    void Draw(float delta_time, const Camera* camera) override;

    //--------------------------------------------------------------------------------//

};
