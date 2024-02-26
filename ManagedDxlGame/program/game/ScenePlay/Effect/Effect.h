#pragma once
#include "../../../wta_library/wta_DrawAnim.h"
#include "../../SceneAll/GameObject.h"

class Character;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �G�t�F�N�g�֌W�̊��N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class Effect : public GameObject
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Effect(tnl::Vector3 pos, Character* character);

	virtual ~Effect();

	//--------------------------------------------------------------------------------//

protected:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �T�C�Y
	int m_size = 30;						
	
	// �G�t�F�N�g�̎�������
	float m_active_time = 0.9f;				
	// �o�ߎ���
	float m_elapsed_time = 0.0f;				

	// �I�t�Z�b�g
	tnl::Vector3 m_offset;					

	// �������t���O
	bool m_is_active = false;			

	// �G�t�F�N�g�̎��
	eEffectPlayerType e_type;				
	
	// �`��A�j���[�V�����|�C���^
	wta::DrawAnim* m_animLoader = nullptr;
	// �L�����N�^�[�|�C���^
	Character *m_character = nullptr;		

	//--------------------------------------------------------------------------------//

public:

	//---------------------------------Setter&Getter---------------------------------//

	// �T�C�Y�̎擾
	int GetSize() const { return  m_size; }
	// �I�t�Z�b�g�̐ݒ�
	// arg ... m_offset(�`����W�̃I�t�Z�b�g)
	void SetOffset(tnl::Vector3 offset) { m_offset = offset; }
	// �s���t���O�̐ݒ�
	// arg ... m_is_active(�������t���O)
	void SetIsActive(bool is_moved) { m_is_active = is_moved; }
	// �s���t���O�̎擾
	bool GetIsActive() const { return m_is_active; }

	//------------------------------------------------------------------------------//
};