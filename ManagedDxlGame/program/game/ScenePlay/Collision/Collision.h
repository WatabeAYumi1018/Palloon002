#pragma once
#include "../../../engine/GameEngine.h"


class Map;
class Character;
class Player;
class Enemy;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �����蔻��̎��ʂƋ�̓I�������s���N���X
//
/////////////////////////////////////////////////////////////////////////////////////////


class Collision
{

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

public:

	Collision();
	~Collision() {}

	//-------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �O��擾�����L�����N�^�[�̍��W
	tnl::Vector3 m_last_chara_pos;								
	// Clear�n�_�̍��W
	tnl::Vector3 m_clear_pos;									
	
	// Clear�t���O
	bool m_is_clear=false;										
	// ��{�^������t���O
	bool m_is_up = false;									    

	// �O��擾���������蔻����
	std::vector<std::vector<sCollisionInfo>> m_cached_chips;	

	//---------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �L�����N�^�[�Ƌ�`�̓����蔻��
	void CheckBoxCollision
	(
		Character* chara
		, Map* map
		, const std::vector<std::vector<sCollisionInfo>>& surroundingChips
	);	
	
	// �L�����N�^�[�Ɛ����̓����蔻��
	void CheckLineCollision
	(
		Character* chara
		, Map* map
		, const std::vector<std::vector<sCollisionInfo>>& surroundingChips
	);	
	
	// �����蔻�肪���݂��邩
	bool IsRowCollisionExists(const std::vector<sCollisionInfo>& rowChips);				

	// �����蔻����擾
	std::vector<sCollisionInfo> GetRowChips
	(
		int chip_x
		, int i
		, int range
		, const Map* map
	);									
	
	// �L�����N�^�[�̎��͂̓����蔻����擾
	std::vector<std::vector<sCollisionInfo>> GetSurroundingChips
	(
		Character* chara
		, Map* map
		, int range
	);					

public:

	// �����蔻��̌v�Z
	// arg1 ... �L�����N�^�[�̃|�C���^
	// arg2 ... �}�b�v�̃|�C���^
	// args3 ... �����蔻�茟�m�͈̔�
	// tips1 ... �I�u�W�F�N�g�𐶐����Ă���ScenePlay���ŌĂяo���܂�
	// tips2 ... �����蔻��Ɋւ��鏈���̒��ŌĂяo���܂�
	void CollisionCalculate(Character* chara, Map* map, int range);			
	// �L�����N�^�[���m�̓����蔻��
	// arg1 ... �v���C���[�̃|�C���^
	// arg2 ... �G�̃|�C���^
	// tips1 ... �I�u�W�F�N�g�𐶐����Ă���ScenePlay���ŌĂяo���܂�
	// tips2 ... �����蔻��Ɋւ��鏈���̒��ŌĂяo���܂�
	void CollisionCharacter(Player* player, Enemy* enemy);
	// �L�����N�^�[�̃}�b�v�`�b�v���W���擾
	// arg1 ... �L�����N�^�[�̍��W
	// arg2 ... �}�b�v�̃|�C���^
	// tips1 ... �I�u�W�F�N�g�𐶐����Ă���ScenePlay���ŌĂяo���܂�
	// tips2 ... �����蔻��Ɋւ��鏈���̒��ŌĂяo���܂�
	tnl::Vector3 GetCharacterMapChipPos(const tnl::Vector3& charaPos, const Map* map);

	//---------------------------------------------------------------------------------//


	//----------------------------------Setter&Getter----------------------------------//

	// �N���A������s�����W���擾
	const tnl::Vector3 GetClearPos() const { return m_clear_pos; }
	// �N���A����t���O���擾
	bool GetIsClear() const { return m_is_clear; }
	// ��{�^������t���O���擾
	bool GetIsUp() const { return m_is_up; }

	//---------------------------------------------------------------------------------//
};
