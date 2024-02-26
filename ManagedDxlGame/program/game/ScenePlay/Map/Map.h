#pragma once
#include "../../../engine/GameEngine.h"

class Camera;
class Player;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// csv����̃}�b�v�`�b�v�A�����蔻��̓ǂݎ��
//
/////////////////////////////////////////////////////////////////////////////////////////


class Map final	
{

private:

	//-----------------------------------struct�\��-----------------------------------//

	struct sStageInfo
	{
		// �X�e�[�W��
		std::string s_stage_name;
		// �w�i�摜�̃p�X
		std::string s_background_hdl;
		// �}�b�v�`�b�v�̃p�X
		std::string s_map_csv;
		// �����蔻��̃p�X
		std::string s_collision_csv;
		// �G�̃p�X
		std::string s_enemy_csv;
		// BGM�̃p�X
		std::string s_music_bgm;
		// �v���C���[�̏������W
		tnl::Vector3 s_initial_player_pos;
	};

	//--------------------------------------------------------------------------------//

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	explicit Map(const std::string& stageName);

	virtual ~Map();

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�ϐ�-----------------------------------//
	
	// ����
	static const int MAP_ROW_COL = 7;			
	// �c��
	static const int MAP_ALL_NUM = 49;			
	// �}�b�v�`�b�v�̃T�C�Y
	static const int MAP_CHIP_SIZE = 32;		

private:

	// �}�b�v�`�b�v�̃n���h��
	int m_map_hdl[MAP_ALL_NUM];									
	
	// �}�b�v�`�b�v�̍��W
	tnl::Vector3 m_pos;											
	
	// �}�b�v�`�b�v�̕`����
	std::vector<std::vector<int>> m_csv_map_tile;				
	// �}�b�v�`�b�v�̓����蔻��`����
	std::vector<std::vector<int>> m_csv_collision;				
	// �}�b�v�`�b�v�̓����蔻����
	std::vector<std::vector<sCollisionInfo>> m_collision_info;	
	// �e�X�e�[�W�̏��
	std::vector<sStageInfo> m_stageList =						
	{ 
		{
			"stage1"
			,"graphics/stage1-1.jpg"
			,"csv/stage1-1.csv"
			,"csv/stage1-1collision.csv"
			,"csv/stage1-1enemy.csv"
			,"music/stage1-1.mp3"
			,{0,100,0}
		},

		{
			"stage2"
			,"graphics/stage1-2.png"
			,"csv/stage1-2.csv"
			,"csv/stage1-2collision.csv"
			,"csv/stage1-2enemy.csv"
			,"music/stage1-2.mp3"
			,{0,5800,0}
		},
		
		{
			"stage3"
			,"graphics/stage1-3.png"
			,"csv/stage1-3.csv"
			,"csv/stage1-3collision.csv"
			,"csv/stage1-3enemy.csv"
			,"music/stage1-3.mp3"
			,{100,300,0}
		},

		{
			"stageBoss"
			,"graphics/stageBoss.png"
			,"csv/stageBOSS.csv"
			,"csv/stageBOSScollision.csv"
			,"csv/stageBOSSenemy.csv"
			,"music/stageBoss.mp3"
			,{0,300,0}
		}
	};																						

	// ���݂̃X�e�[�W���
	sStageInfo s_current_stage_info;							

public:

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �����蔻���p�̃}�b�v�֐�
	// tips1 ... �J�����ړ��ɂ��X�V���K�v�ȏ����ł�
	// tips2 ... ScenePlay�N���X��Update�֐����ŌĂяo���܂�
	void LoadMapCollision();									
	
	void Initialize(const std::string& stageName);

	void Draw(const Camera* camera);

	void Finalize();

	//--------------------------------------------------------------------------------//


	//---------------------------------Setter&Getter---------------------------------//

	// �}�b�v�`�b�v�̉������擾
	const size_t GetMapChipX() const { return m_csv_map_tile[0].size(); }

	// �}�b�v�`�b�v�̏c�����擾
	const size_t GetMapChipY() const { return m_csv_map_tile.size(); }
	
	// �����蔻������擾
	const std::vector<std::vector<sCollisionInfo>>& GetCollisionInfo() const 
	{
		return m_collision_info; 
	}
	
	// ���݂̃X�e�[�W�����擾
	const sStageInfo& GetCurrentStageInfo() const 
	{
		return s_current_stage_info; 
	}

	// �X�e�[�W�����擾
	const std::vector<sStageInfo> GetStageList() const { return m_stageList; }

	//--------------------------------------------------------------------------------//
};