#pragma once

class SceneBase;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �Q�[���S�̂��Ǘ�����N���X�i�V���O���g���j
//
/////////////////////////////////////////////////////////////////////////////////////////


class SceneManager
{

private:
	
	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//
	
	// �ŏ��̃V�[����ݒ肵�Amain�N���X��Start�֐��ɂČĂяo���܂�
	// ex ... SceneManager::GetInstance(new SceneTitle());�j
 	explicit SceneManager(SceneBase* start_scene);

	//-------------------------------------------------------------------------------//
	
	
	//----------------------------------�V�[�P���X----------------------------------//
	
	// �V�[���J��
	tnl::Sequence<SceneManager> m_sequence 
		= tnl::Sequence<SceneManager>(this, &SceneManager::SeqTransIn);
	
	//-------------------------------------------------------------------------------//


	//-----------------------------------�����o�ϐ�-----------------------------------//
	
	// �t�F�[�h�A�E�g�̉摜�n���h��
	int m_tansition_hdl = 0;
	// �V�[���J�ڂ̎���
	float m_elapsed_time = 0.5f;
	
	//���݂̃V�[��
	SceneBase* m_now_scene= nullptr;
	//���̃V�[��
	SceneBase* m_next_scene = nullptr;

	//-------------------------------------------------------------------------------//


	//----------------------------------�����o�֐�----------------------------------//
	
	// �V�[���J�ځi�t�F�[�h�C���j
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... �V�[�P���X�ɂčŏ��ɌĂ΂��֐��ł�
	bool SeqTransIn(const float delta_time);
	// �V�[���J�ځi�t�F�[�h�A�E�g�j
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... �V�[�P���X�ɂčŌ�ɌĂ΂��֐��ł�
	bool SeqTransOut(const float delta_time);
	// �V�[�����s
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... �V�[�P���X��change�֐��ɂăt�F�[�h�C�����s��ɌĂ΂��֐��ł�
	bool SeqRunScene(const float delta_time);

public:

	// �V�[���J��
	// arg1 ... ���̃V�[��
	// arg2 ... �t�F�[�h�A�E�g�̎���(�f�t�H���g��0.5f)
	// tips ... �e��V�[���ɂđJ�ڂ̍ۂɌĂяo���܂�
	// ex ... SceneManager::GetInstance()->ChangeScene(new SceneTitle());
	void ChangeScene(SceneBase* next_scene, float trans_time = 0.5f);
	
	void Update(float delta_time);


	//-----static�֐�-----//

	// �C���X�^���X�̎擾
	// arg ... �ŏ��̃V�[��(�f�t�H���g��nullptr����)
	// tips ... �N�����Ɉ�x�����Ăяo���܂�
	// ex ... SceneManager::GetInstance(new SceneTitle());�j
	static SceneManager* GetInstance(SceneBase* start_scene = nullptr);
	
	static void Finalize();
	
	//--------------------//

	//-------------------------------------------------------------------------------//

};