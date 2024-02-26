#pragma once
#include "../../../../engine/GameEngine.h"
#include "Enemy.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �G�N���X�F�h���S���i�ꊇ�Ǘ��j
//
/////////////////////////////////////////////////////////////////////////////////////////

class EnemyDoragon :public Enemy
{

public:
	
	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	EnemyDoragon
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		, Player* player
		, Map* map
		, Collision* collision
		, Camera* camera
	);
	
	~EnemyDoragon();

	//---------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �R���[�`���V�[�P���X
	TNL_CO_SEQUENCE(EnemyDoragon, &EnemyDoragon::SeqIdle);						

	//-------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//
	
	// ���s��
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �R���[�`���ɂ���čŏ��ɌĂяo����܂�
	// tips2 ... �֐��Ō�ɂ�TNL_SEQ_CO_CONTINUE;��K���Ԃ��Ă�������
	// exe ... tnl_sequence_.change(&EnemyDoragon::SeqIdle);
	bool SeqIdle(const float delta_time);
	// �t�@�C�A�{�[���U��
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �R���[�`���ɂ���ČĂяo����܂�
	// tips2 ... �֐��Ō�ɂ�TNL_SEQ_CO_CONTINUE;��K���Ԃ��Ă�������
	// exe ... tnl_sequence_.change(&EnemyDoragon::SeqFireBall);
	bool SeqFireBall(const float delta_time);								
	// �t���C���U��
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �R���[�`���ɂ���ČĂяo����܂�
	// tips2 ... �֐��Ō�ɂ�TNL_SEQ_CO_CONTINUE;��K���Ԃ��Ă�������
	// exe ... tnl_sequence_.change(&EnemyDoragon::SeqFlame);
	bool SeqFlame(const float delta_time);									

public:
	
	void Update(const float delta_time) override;	
	
	void Draw(const float delta_time, const Camera* camera) override;		

	//-------------------------------------------------------------------------------//
};