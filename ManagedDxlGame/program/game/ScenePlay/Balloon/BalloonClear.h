#pragma once
#include "../../../engine/GameEngine.h"
#include "../../SceneAll/GameObject.h"

class Player;
class Camera;
class Collision;


/////////////////////////////////////////////////////////////////////////////////////////
// 
//�N���A���D�N���X�i�`��ƍX�V�j
//
/////////////////////////////////////////////////////////////////////////////////////////


class BalloonClear : public GameObject
{

private:

	//-----------------------------------enum�N���X-----------------------------------//

	enum class eBalloonState
	{
		Hidden,
		Rising,
		Floating,
		ClearRising
	};

	//--------------------------------------------------------------------------------//

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	explicit BalloonClear(Collision* collision);

	~BalloonClear() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �_�ŊԊu
	const float BLINK_INTERVAL = 2.0f;
	// ���D�̃n���h��(Rising,Floating)
	int m_balloon_hdl = 0;
	// ���D�̃n���h��(ClearRising)
	int m_balloon_clear_hdl = 0;
	// �{�^������\���̃n���h��
	int m_clear_up_hdl = 0;

	// ���V����
	float m_float_time = 0.0f;
	// ���V�̍��W��
	float m_offset_y = 10.0f;
	// ���V�̑��x
	float m_velocity_y = 100.0f;
	// ����{�^���̓_�Ŏ���
	float m_blink_time = 0.0f;

	// ���D�̃T�C�Y
	tnl::Vector3 m_size = { 300,500,0 };
	// ���D�̈ʒu(���W�̌�t����`�p)
	tnl::Vector3 m_target_pos;

	// �摜�̐؂�ւ��t���O
	bool m_is_change_grahic = false;
	// �`��t���O
	bool m_is_draw = false;

	// enum�N���X�Ŋe���D�̉摜�Ə�Ԃ��Ǘ��i������Ԃ�Hidden�j
	eBalloonState e_balloon_state = eBalloonState::Hidden;

	// �����蔻��̃|�C���^
	Collision* m_collision = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �N���A���W�̍X�V
	// tips ... Update�֐����ŌĂяo���܂�
	void ClearPosChange();
	// ���D�̈ړ��i�N���A���̕��D�̉��o�Ɋւ��鏈���j
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	// tips ... Update�֐����ŌĂяo���܂�
	void MoveBalloon(float delta_time);

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(float delta_time, const Camera* camera) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �N���A�O���t�B�b�N�ւ̐؂�ւ��t���O���擾
	bool GetIsChangeGraphic() const { return m_is_change_grahic; }
	// �`��t���O�̐ݒ�
	// arg ... m_is_draw(�`��t���O)
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }

	//-------------------------------------------------------------------------------//
};