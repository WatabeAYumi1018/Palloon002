#pragma once
#include "../../engine/sceneBase.h"
#include "../SceneAll/GameObject.h"
#include "../SceneAll/Music/MusicManager.h"


class BackGround;
class Camera;
class Map;
class Collision;
class BalloonInstruction;
class BalloonClear;
class EnemyLoad;
class Enemy;
class Player;
class EffectPlayer;
class EffectBoss;
class Wind;
class UI;
class Logo;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// scene���ŕK�v�ȑS�Ă̗v�f���Ǘ�����N���X
// �|�����[�t�B�Y���̂��߁A�������������������ōs���i�����蔻��Ȃǁj
//
/////////////////////////////////////////////////////////////////////////////////////////


class ScenePlay : public SceneBase 
{

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	explicit ScenePlay(const std::string& stageName);

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//
	

	// �X�e�[�W�R�ł̓G�̍ő�Đ�����
	const int ENEMY_TOTAL_RESPAWNS = 10;								

	// �G�̍Đ����񐔂��J�E���g
	int m_enemy_respawn_count = 0;									
	// �G�̍Đ�������
	float m_enemy_respawn_time= 0.0f;									

	// �V�[���ύX�t���O
	bool m_is_change_scene = false;
	// �G�t�F�N�g�t���O
	bool m_is_effect = false;

	// �X�e�[�W��
	std::string m_stage_name;

	// ���������I�u�W�F�N�g�p�̃��X�g
	std::list<GameObject*> m_gameObjects;						
	// ���������G�p�̃��X�g
	std::list<Enemy*> m_enemies;								
	// �폜�\��̓G�p�̃��X�g
	std::list<Enemy*> m_enemies_remove_list;					
	// �G��ID�Ə��̃y�A(��������G�̎�ނ�ID�ŊǗ����邽��)
	std::map<int, sEnemyInfo> m_enemy_infos;					
	// ���X�|�[������G�̃|�C���^�ƍĐ����܂ł̕b��
	std::list<std::pair<Enemy*, float>> m_enemies_respawn_list;	
	
	// �V�[�P���X
	tnl::Sequence<ScenePlay> m_sequence 
		= tnl::Sequence<ScenePlay>(this, &ScenePlay::SeqIdle);

	// �w�i�̃|�C���^
	BackGround* m_backGround = nullptr;
	// �J�����̃|�C���^
	Camera* m_camera = nullptr;
	// �}�b�v�̃|�C���^
	Map* m_map = nullptr;
	// �����蔻��̃|�C���^
	Collision* m_collision = nullptr;
	// ��������o���[���̃|�C���^
	BalloonInstruction* m_balloonInstruction = nullptr;
	// �N���A�o���[���̃|�C���^
	BalloonClear* m_balloonClear = nullptr;
	// �G�̏��̓ǂݎ��
	EnemyLoad* m_enemyLoad = nullptr;
	// �G�̃|�C���^
	Enemy* m_enemy = nullptr;
	// �v���C���[�̃|�C���^
	Player* m_player = nullptr;
	// �v���C���[�G�t�F�N�g�̃|�C���^�i�r�[���U���j
	EffectPlayer* m_effectPlayer_beam = nullptr;
	// �v���C���[�G�t�F�N�g�̃|�C���^�i�t�@�C�A�U���j
	EffectPlayer* m_effectPlayer_fire = nullptr;
	// �{�X�G�t�F�N�g�̃|�C���^
	EffectBoss* m_effectBoss = nullptr;
	// ���̃|�C���^�i�X�e�[�W�Q�j
	Wind* m_wind = nullptr;
	// UI�̃|�C���^
	UI* m_ui = nullptr;
	// ���S�̃|�C���^
	Logo* m_logo = nullptr;

	//--------------------------------------------------------------------------------//


	//-----------------------------------�����o�֐�-----------------------------------//

	// �������
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips... �V�[�P���X�ɂčŏ��ɌĂ΂��֐��ł�
	bool SeqIdle(float delta_time);

	// �G�̏��̓ǂݎ��Ə�����
	// tips ... Initialize�֐����ŌĂяo���܂�
	void InitEnemy();
	// ���y���̓ǂݎ��Ə�����
	// tips ... SeqIdle�֐���isStart�֐����ŌĂяo���܂�
	void InitMusic();
	// �G�t�F�N�g����
	// tips ... Update�֐����ŌĂяo���܂�
	void CreateEffect();	
	// �G����
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... Update�֐����ŌĂяo���܂�
	// tips2 ... stage3�݂̂Ŏg�p���܂�
	void CreateEnemy(float delta_time);							
	// �{�X�̃G�t�F�N�g�Ƃ̓����蔻��
	// tips1 ... CollisionCheck�֐����ŌĂяo���܂�
	// tips2 ... stageBoss�݂̂Ŏg�p���܂�
	void CollisionCheckBoss();
	// �v���C���[�ƓG�̒ʏ퓖���蔻��
	// tips1 ... Update�֐����ŌĂяo���܂�
	void CollisionCheck(float delta_time);						
	// �G�̍폜�ƃ��������
	// tips ... Finalize�֐����ŌĂяo���܂�
	void RemoveAndDelete();		

public:

	void Initialize() override;

	void Update(float delta_time) override;

	void Draw(float delta_time) override;

	void Finalize() override;

	//--------------------------------------------------------------------------------//
};