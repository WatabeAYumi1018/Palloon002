#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �G�N���X�F�d���i�ꊇ�Ǘ��j
//
/////////////////////////////////////////////////////////////////////////////////////////


class EnemyFairy :public Enemy
{

private:

	//-----------------------------------enum�N���X-----------------------------------//

	enum sFairyType
	{
		Peach,
		Blue,
		Yellow
	};

	//--------------------------------------------------------------------------------//

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	EnemyFairy
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		, Player* player
		, Map* map
		, Collision* collision
		, Camera* camera
	);
	
	~EnemyFairy();

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �d���̎�ށi�O���t�B�b�N�̈Ⴂ�j
	sFairyType s_type;												
	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(EnemyFairy, &EnemyFairy::SeqIdle);						


	//-------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//
	
	// ���s��
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �R���[�`���ɂ���čŏ��ɌĂяo����܂�
	// tips2 ... �֐��Ō�ɂ�TNL_SEQ_CO_CONTINUE;��K���Ԃ��Ă�������
	// exe ... tnl_sequence_.change(&EnemyFairy::SeqIdle);
	bool SeqIdle(const float delta_time);										
	// �ړ�����
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �R���[�`���ɂ���ČĂяo����܂�
	// tips2 ... �֐��Ō�ɂ�TNL_SEQ_CO_CONTINUE;��K���Ԃ��Ă�������
	// exe ... tnl_sequence_.change(&EnemyFairy::SeqMove);
	bool SeqMove(const float delta_time);
	// �U������
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �R���[�`���ɂ���ČĂяo����܂�
	// tips2 ... �֐��Ō�ɂ�TNL_SEQ_CO_CONTINUE;��K���Ԃ��Ă�������
	// exe ... tnl_sequence_.change(&EnemyFairy::SeqAttack);
	bool SeqAttack(const float delta_time);

public:
	
	// �����_���Ŏ�ނ�����
	void RandomType();														

	void Update(const float delta_time) override;	

	void Draw(const float delta_time, const Camera* camera) override;		

	//-------------------------------------------------------------------------------//
};
