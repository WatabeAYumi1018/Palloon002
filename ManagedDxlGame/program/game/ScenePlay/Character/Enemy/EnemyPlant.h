#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"



/////////////////////////////////////////////////////////////////////////////////////////
// 
// �G�N���X�F�A���i�ꊇ�Ǘ��j
//
/////////////////////////////////////////////////////////////////////////////////////////


class EnemyPlant :public Enemy
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	EnemyPlant
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		,Player *player
		, Map* map
		, Collision* collision
		, Camera* camera
	);
	
	~EnemyPlant();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(EnemyPlant, &EnemyPlant::SeqIdle);						

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// ���s��
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �R���[�`���ɂ���čŏ��ɌĂяo����܂�
	// tips2 ... �֐��Ō�ɂ�TNL_SEQ_CO_CONTINUE;��K���Ԃ��Ă�������
	// exe ... tnl_sequence_.change(&EnemyFairy::SeqIdle);
	bool SeqIdle(const float delta_time);
	// �U������
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �R���[�`���ɂ���ČĂяo����܂�
	// tips2 ... �֐��Ō�ɂ�TNL_SEQ_CO_CONTINUE;��K���Ԃ��Ă�������
	// exe ... tnl_sequence_.change(&EnemyFairy::SeqAttack);
	bool SeqAttack(const float delta_time);
public:

	void Update(const float delta_time) override;

	void Draw(const float delta_time, const Camera* camera) override;		

	//---------------------------------------------------------------------------------//
};
