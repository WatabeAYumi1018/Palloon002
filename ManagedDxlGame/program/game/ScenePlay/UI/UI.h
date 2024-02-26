#pragma once
#include "../../../engine/GameEngine.h"
#include "../../SceneAll/GameObject.h"

class Camera;
class Player;
class Enemy;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// UI�̏����ꊇ���s���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////

class UI : public GameObject
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	UI(Player* player, Enemy* enemy);

	virtual ~UI() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// HP�o���[���̉���
	const int BALLON_WIDTH = 65;

	// �v���C���[�o���[���̕`��Ԋu
	const int BALLON_INTERVAL_PLAYER = 70;
	// �v���C���[�o���[���̕`��J�nY���W
	const int BALLON_PLAYER_START_Y = 650;
	// �v���C���[�o���[���̕`��I��Y���W
	const int BALLON_PLAYER_END_Y = 720;

	// �{�X�o���[���̕`��Ԋu
	const int BALLON_INTERVAL_BOSS = 50;
	// �{�X�o���[���̕`��I��Y���W
	const int BALLON_BOSS_END_Y = 65;

	// �v���C���[��HP�o���[��
	int m_hp_player_hdl = 0;
	// �{�X��HP�o���[��
	int m_hp_boss_hdl = 0;

	// HP�̕`��t���O�i�{�X�̂ݕ`��j
	bool m_is_draw = false;

	// �v���C���[�̃|�C���^
	Player* m_player = nullptr;
	// �{�X�̃|�C���^
	Enemy* m_enemy = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �v���C���[��HP�o���[���̕`�揈��
	// tips ... Draw�֐����ŌĂяo���܂�
	void HpPlayerBalloons();
	// �{�X��HP�o���[���̕`�揈��
	// tips ... Draw�֐����ŌĂяo���܂�
	void HpBossBallons();

public:

	void Initialize() override;

	void Draw(float delta_time, const Camera* camera) override;

	//--------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �`��t���O�̐ݒ�
	// arg ... m_is_draw(�`��t���O)
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }

	//--------------------------------------------------------------------------------//
};
