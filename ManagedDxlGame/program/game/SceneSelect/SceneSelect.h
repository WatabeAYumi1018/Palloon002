#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/Music/MusicManager.h"

class GameObject;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �Q�[���Z���N�g�̃V�[���i�`���X�V�̑��A�Z���N�g��ʓ��ł̋������j
//
/////////////////////////////////////////////////////////////////////////////////////////


class SceneSelect : public SceneBase 
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	SceneSelect();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//
	
	//�X�e�[�W��
	const int STAGE_NUM = 4;					

	// �w�i�摜�̃n���h��
	int m_back_hdl = 0;
	// �X�e�[�W�P�̃n���h��
	int m_stage1_hdl = 0;
	// �X�e�[�W�Q�̃n���h��
	int m_stage2_hdl = 0;
	// �X�e�[�W�R�̃n���h��
	int m_stage3_hdl = 0;
	// �{�X�X�e�[�W�̃n���h��
	int m_boss_hdl = 0;
	
	// �I�𒆃X�e�[�W
	int m_selected_stage = 0;					

	// �I�𒆕��D�̏㉺�^�C�}�[
	float m_balloon_time = 0.0f;			
	// �㉺�I�t�Z�b�g
	float m_balloon_offset_y = 10.0f;		
	// �㉺���x
	float m_balloon_velocity_y = 5.0f;			

	// �X�e�[�W��
	std::vector<std::string> m_stage_names;		

	// �V�[�P���X�i�I�𒆂̃X�e�[�W���j
	tnl::Sequence<SceneSelect> m_sequence
		= tnl::Sequence<SceneSelect>(this, &SceneSelect::SeqIdle);


	//-------�Q�[���X�e�B�b�N�p--------//

	// 0.5�b�̓��̓N�[���_�E��
	const float INPUT_COUNTDOWN_TIME = 0.5f;	
	// 20%�̃f�b�h�]�[��(���͖����͈�)
	const float DEADZONE = 0.2f;		

	// �A�i���O�X�e�B�b�N�̌X���x�N�g��
	int m_input_x =0;

	int m_input_y =0;

	// ���K�����ꂽ���͒l
	float m_normalized_input_x;					
	// ���̓N�[���_�E���^�C�}�[
	float m_input_cooldown_time = 0.0f;				
	// �O��̓��͒l
	float m_previous_input_x = 0.0f;

	//----------------------------------//

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//
	
	// �������
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... �V�[�P���X�ɂčŏ��ɌĂ΂��֐��ł�
	bool SeqIdle(float delta_time);
	// �I�𒆂̕��D�̏㉺�ړ�
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... ���t���[�����s����֐��ł�
	void MoveBalloon(float delta_time);			

public:

	void Update(float delta_time) override;

	void Draw(float delta_time) override;
	
	void Finalize() override;

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// �I�𒆂̃X�e�[�W�����擾
	// tips... ScenePlay�̃R���X�g���N�^�����Ƃ��Ďg�p���܂�
	// ex ...  new ScenePlay(GetSelectedStage());
	std::string GetSelectedStage() const 
	{
		return m_stage_names[m_selected_stage]; 
	};

	//--------------------------------------------------------------------------------//
};

