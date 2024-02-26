#pragma once
#include "../../SceneAll/GameObject.h"
#include "../../../wta_library/wta_DrawAnim.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �����A�G�̊��N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class Character :public GameObject
{

public:
	
	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Character
	(
		const tnl::Vector3 pos
		, int size
		, int hp
		, const tnl::Vector3 velocity
	);
	
	virtual ~Character();

	//---------------------------------------------------------------------------------//

protected:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �����蔻��p�T�C�Y
	int m_size;										
	// HP
	int m_hp;										
	
	// ���G����
	float m_invincible_time = 0.0f;					
	
	// ���x
	tnl::Vector3 m_velocity = { 100,0,0 };			
	// �d��
	tnl::Vector3 m_gravity = { 0,100,0 };			
	
	// �ڒn��
	bool m_is_ground = true;						
	// ���S
	bool m_is_dead = false;							
	// ����
	bool m_is_direction_right = true;				
	// ���G
	bool m_is_invincible = false;					

	// �`��A�j���[�V�����|�C���^
	wta::DrawAnim* m_animLoader = nullptr;		

	//---------------------------------------------------------------------------------//

public:

	//-----------------------------------�����o�֐�-----------------------------------//

	// HP�̌���
	// arg ... �_���[�W��(��{�P�����炵�܂�)
	// tips ... �����蔻��ɏ����鏈�����ɂČĂяo���܂�
	void DecreaseHP(int damage);				
	// ���G��Ԃɂ���
	// tips ... �����蔻��ɏ����鏈�����ɂČĂяo���܂�
	void MakeInvincible();						
	// ���G���Ԃ̏���
	// arg ... delta_time(�O�t���[������̌o�ߎ���)
	// tips ... Update���ɂČĂяo���܂�
	void Invincible(float delta_time);			

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// �����蔻��p�T�C�Y�̎擾
	int GetSize() const { return m_size; }
	// HP�̎擾
	int GetHp() const { return m_hp; }
	// ���S�t���O�̐ݒ�
	// arg ... m_is_dead(�L�����N�^�[�̎��S�t���O)
	void SetIsDead(bool is_dead) { m_is_dead = is_dead; }
	// ���S�t���O�̎擾
	int GetIsDead() const { return m_is_dead; }
	// �����̎擾
	bool GetIsDirectionRight() const { return m_is_direction_right; }
	// ���G���Ԃ̎擾
	bool GetIsInvincible() const { return m_is_invincible; }

	//---------------------------------------------------------------------------------//
};