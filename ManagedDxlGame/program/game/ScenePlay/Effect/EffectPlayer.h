#pragma once
#include "../engine/GameEngine.h"
#include "Effect.h"

class Player;


/////////////////////////////////////////////////////////////////////////////////////////
// 
//	�v���C���[�G�t�F�N�g�̃N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class EffectPlayer : public Effect
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	EffectPlayer(Player *player, eEffectPlayerType effectType);

	~EffectPlayer();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �r�[���U���ł̓����蔻���5�̉~�̍��W
	std::vector<tnl::Vector3> m_collision_circles_pos;			

	// �G�t�F�N�g�̎��
	eEffectPlayerType m_effectType = eEffectPlayerType::None;	
	
	// �v���C���[�̃|�C���^
	Player* m_player = nullptr;				
	
	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �r�[���U���̏���
	// tips ... EffectHandle�֐����ŌĂяo���܂�
	void EffectBeamHandle();
	// �t�@�C�A�U���̏���
	// tips ... EffectHandle�֐����ŌĂяo���܂�
	void EffectFireHandle();
	// �G�t�F�N�g�U���̑�������
	// tips ... Update�֐����ŌĂяo���܂�
	void EffectHandle();

public:

	// �~�̍��W���v�Z
	// tips ... Update�֐����ŌĂяo���܂�
	void CalculateCollisionCircles();							

	void Update(float delta_time) override;

	void Draw(float delta_time, const Camera* camera) override;

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �����蔻���5�̉~�̍��W���擾
	std::vector<tnl::Vector3> GetCollisionCirclesPos() const 
	{
		return m_collision_circles_pos; 
	}

	//---------------------------------------------------------------------------------//
};