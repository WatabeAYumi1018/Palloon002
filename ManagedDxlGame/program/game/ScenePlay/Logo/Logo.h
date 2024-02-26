#pragma once
#include "../../SceneAll/GameObject.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �N���A�A�Q�[���I�[�o�[�̃��S���Ǘ�����N���X
//
/////////////////////////////////////////////////////////////////////////////////////////

class Logo :public GameObject
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Logo();
	~Logo();

	//-------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �_�Ŏ���
	const float BLINK_ELAPSED_TIME = 2.0f;

	// �I�����̃{�^���\���摜
	int m_clear_botton_hdl = 0;
	// �N���A���̃��S�摜
	int m_clear_logo_hdl = 0;
	// HP0�ɂȂ������̃��S�摜
	int m_burst_logo_hdl = 0;
	// �����������̃��S�摜
	int m_fall_logo_hdl = 0;
	
	// �{�^���摜�̃T�C�Y
	int m_botton_size = 150;
	// ���S�̕`��T�C�Y(X)
	int m_result_x_size = 400;
	// ���S�̕`��T�C�Y(Y)
	int m_result_y_size = 200;

	// �o�ߎ���
	float m_blink_elapsed_time = 0.0f;

	// �N���A�t���O
	bool m_is_clear = false;
	// �`��t���O
	bool m_is_draw = false;

	// ���S�̎��
	eLogoType e_logo_type = eLogoType::None;

	//---------------------------------------------------------------------------------//

public:

	//-----------------------------------�����o�֐�-----------------------------------//

	void Update(float delta_time) override;

	void Draw(float delta_time, const Camera* camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �N���A�t���O�̐ݒ�
	// arg ... m_is_clear(�N���A�t���O)
	void SetIsClear(bool is_clear) { m_is_clear = is_clear; }

	// ���S�̃^�C�v��ݒ�
	// arg ... e_logo_type(���S�̎��)
	void SetLogoState(eLogoType logo_state) { e_logo_type = logo_state; }

	//---------------------------------------------------------------------------------//
};
