#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/Music/MusicManager.h"
#include "../SceneAll/Balloon/Balloon.h"

class GameObject;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �Q�[���^�C�g���̃V�[���i�`���X�V�̑��A�^�C�g�����ł̋������j
//
/////////////////////////////////////////////////////////////////////////////////////////


class SceneTitle : public SceneBase 
{

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �ő�o�E���h��
	const int MAX_BOUNDE = 2;							
	// �n�ʂ�Y�ʒu
	const float GROUND_Y = 50;							
	// �o�E���h���̑��x�̌�����
	const float BOUND_RATE = -1.0f;						
	// ���S�̕\������
	const float DISPLAY_TIME = 100;	
	// ���D�̐�����
	const int BALLOON_SPAWN = 20;						
	// ���D�̐����Ԋu
	const float SPAWN_INTERVSL = 0.5f;					

	// �w�i�̃n���h��
	int m_back_hdl = 0;
	// �^�C�g�����S�̃n���h��
	int m_logo_hdl = 0;
	// �L�����N�^�[�̃n���h��
	int m_palloon_hdl = 0;	
	// �L�����N�^�[�̃o�E���h��
	int m_bound_count = 0;
	
	// ���S�̕\����
	float m_current_width = 0;
	// ���S�̕`�掞��
	float m_balloon_spawn_timer = 0.0f;

	// ���S�̕\���t���O
	bool m_is_logo_displayed = false;

	// �C���X�g�̏���Y�ʒu�B��ʊO�㕔�ɐݒ�
	tnl::Vector3 m_chara_pos = { 0,-360,0 };		
	// �����̉������̑��x
	tnl::Vector3 m_velocity = {0,1,0};		
	// �d�͂̋���
	tnl::Vector3 m_gravity = {0,0.1f,0};				
	
	// �o���[���̔z��
	std::vector<Balloon> balloons;						

	// �V�[�P���X
	tnl::Sequence<SceneTitle> m_sequence 
		= tnl::Sequence<SceneTitle>(this, &SceneTitle::SeqIdle);

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �������
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... �V�[�P���X�ɂčŏ��ɌĂ΂��֐��ł�
	bool SeqIdle(float delta_time);

	// ���S�̕\��
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... ���S�̏����𖈃t���[���s���܂�
	void LogoHandle(float delta_time);					
	// �o�E���h�̏���
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... �o�E���h�̏����𖈃t���[���s���܂�
	void BoundHandle(float delta_time);				
	// �o���[���̐���
	// tips ... SeqIdle�֐����s���AisStart()�ɂ���Ĉ�x�����Ă΂�܂�
	void SpawnBalloon();							

public:

	void Update(float delta_time) override;

	void Draw(float delta_time) override;
	
	void Finalize() override;

	//--------------------------------------------------------------------------------//
};
