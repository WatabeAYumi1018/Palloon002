#pragma once
#include "../../../../library/tnl_sequence.h"
#include "../../../../engine/GameEngine.h"
#include "../Character.h"

class Collision;
class Camera;
class Player;
class Map;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �G�̊��N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class Enemy :public Character
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Enemy
	(
		const sEnemyPosData& data
		, const sEnemyInfo& info
		,Player* player
		,Map*map
		,Collision * collision
		,Camera* camera
	);
	
	virtual ~Enemy() {}

	//--------------------------------------------------------------------------------//

protected:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// ID
	int m_type_id;											
		
	// �^�C�v(���)
	std::string m_type;										
	// �F
	std::string m_color;									
	
	// �U�����t���O
	bool m_is_active = true;								
	// �{�X�U�����t���O
	bool m_is_active_boss = false;							
	// �{�X�̃t�@�C�A�{�[���U���t���O
	bool m_is_fireball = false;								
	// �{�X�̃t���C���U���t���O
	bool m_is_flame = false;

	// �G�̍��W�f�[�^(�\����)
	sEnemyPosData s_date;

	// �v���C���[�̃|�C���^
	Player* m_player = nullptr;
	// �}�b�v�̃|�C���^
	Map* m_map = nullptr;
	// �����蔻��̃|�C���^
	Collision * m_collision = nullptr;
	// �J�����̃|�C���^
	Camera* m_camera = nullptr;

	//-------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �v���C���[�Ƃ̋����v�Z
	float DistanceCalc();									
	
public:

	// �E�ւ̈ړ��\����
	// tips ... ���̊֐��́A�G�̈ړ������i�R���[�`���j�Ŏg�p����
	bool CanMoveRight();
	// ���ւ̈ړ��\����
	// tips ... ���̊֐��́A�G�̈ړ������i�R���[�`���j�Ŏg�p����
	bool CanMoveLeft();

	virtual void Update(const float delta_time)  {}

	virtual void Draw(const float delta_time, const Camera* camera)  {}	

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// ID�̎擾
	int GetTypeID() const { return m_type_id; }

	// �{�X�̍s���t���O�̐ݒ�
	// arg ... m_is_active_boss(�{�X�̍s���t���O)
	void SetIsActiveBoss(const bool is_active_boss)
	{
		m_is_active_boss = is_active_boss; 
	}
	// �{�X�̍s���t���O�̎擾
	bool GetIsActiveBoss() const { return m_is_active_boss; }

	// �{�X�̃t�@�C�A�{�[���U���t���O�̎擾
	bool GetIsFireBall() const { return m_is_fireball; }
	// �{�X�̃t���C���U���t���O�̎擾
	bool GetIsFlame() const { return m_is_flame; }

	// �G�̃f�[�^(�\����)�̎擾
	const sEnemyPosData& GetEnemyData() const { return s_date; }

	//-------------------------------------------------------------------------------//
};

// ��
// ����͓G���ɃN���X���쐬���܂������A
// ������K�v�����Ȃ��Ɣ��f�������߁i�����悤�ȃN���X���d�����Ă��܂��Ă��邽�߁j
// ����́A�N���X�̓�����l���Ă��܂��B
