#pragma once
#include "../dxlib_ext/dxlib_ext.h"


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �����̃N���X����Q�Ƃ���enum�N���X�A�\���̂��`����
//
/////////////////////////////////////////////////////////////////////////////////////////


//----------------------------enum class----------------------------//

// �v���C���[�G�t�F�N�g�̎��
enum class eEffectPlayerType
{
	None,
	Fire,
	Beam,
};

// �{�X�G�t�F�N�g�̎��
enum class eEffectBossType
{
	None,
	FireBall,
	Flame,
};

// �}�b�v�̓����蔻��̎��
enum class eMapCollisionType
{
	None,
	Box,
	Line,
	Clear,
};

// �N���A�A�Q�[���I�[�o�[���̃��S�̎��
enum class eLogoType
{
	None,
	Clear,
	Burst,
	Fall
};

//------------------------------------------------------------------//


//------------------------------�\����------------------------------//

// �����蔻��̏��
struct sCollisionInfo
{
	tnl::Vector3 s_pos;
	int s_size;
	eMapCollisionType s_type;
};

// �G�̍��W���
struct sEnemyPosData
{
	int s_type_id;
	tnl::Vector3 s_pos;
};

// �G�̏��
struct sEnemyInfo
{
	int s_id;
	std::string s_name;
	std::string s_color;
	int s_hp;
	int s_size;
};

//------------------------------------------------------------------//

