#pragma once
#include "../../../../engine/GameEngine.h"
#include "../Character.h"

class Camera;
class Map;
class Collision;
class Wind;
class Logo;


/////////////////////////////////////////////////////////////////////////////////////////
// 
// �v���C���[�N���X�i�ꊇ�Ǘ��j
//
/////////////////////////////////////////////////////////////////////////////////////////


class Player :public Character
{

private:

	//-----------------------------------enum�N���X-----------------------------------//

	// �v���C���[�̃A�N�V����
	enum class ePlayerAction
	{
		Idle_right,
		Idle_left,
		Move_right,
		Move_left,
		Dash_right,
		Dash_left,
		Hover_right,
		Hover_left,
		Hover_end_right,
		Hover_end_left,
		Stamp_right,
		Stamp_left,
		Roll_right,
		Roll_left,
		Fire_right,
		Fire_left,
		Beam_right,
		Beam_left,
	};

	//--------------------------------------------------------------------------------//

public:

	//--------------------------�R���X�g���N�^�A�f�X�g���N�^--------------------------//

	Player
	(
		const tnl::Vector3& initialPos
		, Collision* collision
		, Map* map
		,Wind* wind
		,Logo* logo
	);
	
	virtual ~Player() {}

	//--------------------------------------------------------------------------------//

private:

	//-----------------------------------�����o�ϐ�-----------------------------------//

	// �T�C�Y
	static constexpr int SIZE = 35;						
	// HP
	static constexpr int MAX_HP = 5;					
	// �ړ����x�ipix / fps)
	static constexpr float VELOCITY_X = 100.0f;			
	static constexpr float VELOCITY_Y = 500.0f;
	// �_�b�V���̂������l
	const float DASH_THRESHOLD = 0.8f;					
	// �����̕��V��
	const float HOVER_FIRST_FORCE = 1.2f;	
	// ���V�͂̌�����
	const float HOVER_DECAY_FORCE = 1.0f;				
	// ���n���̃A�N�V�����̎���
	const float STAMP_TIME= 1.5f;						

	// ���݂̕��V��
	float m_hovering_force = 0.0f;						
	// ���n���̃A�N�V�����̃^�C�}�[
	float m_stamp_time = 0.0f;							
	
	// �`��t���O
	bool m_is_draw = true;								
	// �󒆂̃t���O
	bool m_is_hovering = false;							
	// ���~�̃t���O
	bool m_is_hovered = false;							
	// �X�^���v�A�N�V�����̃t���O
	bool m_is_stamp = false;							
	// ���[�����O�A�N�V�����̃t���O
	bool m_is_rolling=false;							

	// ���݂̃A�N�V����
	ePlayerAction e_currentAction 
		= ePlayerAction::Idle_right;

	// �����蔻��̃|�C���^
	Collision* m_collision = nullptr;
	// �}�b�v�̃|�C���^
	Map* m_map = nullptr;
	// ���̃|�C���^�i�X�e�[�W�Q�̂݁j
	Wind* m_wind = nullptr;
	// ���S�̃|�C���^
	Logo* m_logo = nullptr;

	//-------�Q�[���X�e�B�b�N�p--------//

	// �A�i���O�X�e�B�b�N�̌X���x�N�g��
	int m_input_x=0;

	int m_input_y=0;

	// x�������̓��͂̐��K��
	float m_normalized_input_x = 0.0f;							
	
	//---------------------------------//

	//--------------------------------------------------------------------------------//

	
	//-----------------------------------�����o�֐�-----------------------------------//

	// �Q�[���{�^������̐ݒ�
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips ... ���̊֐��́AUpdate�֐����ŌĂяo���܂�
	void MoveHandle(float delta_time);
	// ���͂ɂ��A�j���[�V�����̐ݒ�
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips ... ���̊֐��́AUpdate�֐����ŌĂяo���܂�
	void ActionHandle(float delta_time);		
	// �ړ��͈͂̐���
	// tips ... ���̊֐��́AUpdate�֐����ŌĂяo���܂�
	void MoveRange();							
	// �d�͏���
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips ... ���̊֐��́AUpdate�֐����ŌĂяo���܂�
	void Gravity(float delta_time);		
	// ���̉e���ɂ�鏈��
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... ���̊֐��́AUpdate�֐����ŌĂяo���܂�
	// tips2 ... �������A�X�e�[�W�Q�݂̂Ŏ��s����܂�
	void ApplyWind(float delta_time);			

	// �z�o�����O����
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips ... ���̊֐��́AMoveHandle�֐����ŌĂяo���܂�
	void Hovering(float delta_time);			
	// �z�o�����O����
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... ���̊֐��́AMoveHandle�֐����ŌĂяo���܂�
	// tips2 ... HoveringStartRight�֐���HoveringStartLeft�֐����Ăяo���܂�
	void HoveringDirection(float delta_time);	
	// �z�o�����O�J�n�����i�E�j
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �����ɂ��A�j���[�V�����ݒ�����܂�
	// tips2 ... ���̊֐��́AHoveringDirection�֐����ŌĂяo���܂�
	void HoveringStartRight(float delta_time);
	// �z�o�����O�J�n�����i���j
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips1 ... �����ɂ��A�j���[�V�����ݒ�����܂�
	// tips2 ... ���̊֐��́AHoveringDirection�֐����ŌĂяo���܂�
	void HoveringStartLeft(float delta_time);	

public:

	// ���n���̃A�N�V����
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips ... ���̊֐��́AMoveHandle�֐����ŌĂяo���܂�
	void StampAction(float delta_time);		
	// ���[�����̃A�N�V����
	// arg... delta_time(�O�t���[������̌o�ߎ���)
	// tips ... ���̊֐��́AMoveHandle�֐����ŌĂяo���܂�
	void RollAction(float delta_time);
	// �ڒn����
	// tips ... ���̊֐��́A�������ɂē����蔻��̂��߂Ɏg�p���܂�
	bool CheckIsGround();						

	void Update(float delta_time) override;

	void Draw(float delta_time, const Camera* camera) override;

	//--------------------------------------------------------------------------------//

	
	//---------------------------------Setter&Getter---------------------------------//

	// �`��t���O�̐ݒ�
	// args ... m_is_draw(�`��t���O)
	void SetIsDraw(bool is_draw) { m_is_draw = is_draw; }
	// �`��t���O�̎擾
	bool GetIsDraw() const { return m_is_draw; }
	// �X�^���v�A�N�V�����̃t���O�ݒ�
	// args ... m_is_stamp(�X�^���v�A�N�V�����̃t���O)
	void SetIsStamp(bool is_stamp) { m_is_stamp = is_stamp; }
	// ���[�����O�A�N�V�����̃t���O�擾
	bool GetIsRolling() const { return m_is_rolling; }

	//--------------------------------------------------------------------------------//
};


// ��
// ����̓v���C���[�Ɋւ��鏈�����ꊇ�Œ�`���܂������A
// �N���X�̐ӔC�𕪂��邱�Ƃ�����̉ۑ�ł��B
// �`��݂̂��Ǘ�����playerDraw�N���X�A���W�ړ���playerMove�N���X�Ȃ�
// �P�̃N���X�ɕ����̐ӔC���������Ȃ��悤�ɂ��邱�Ƃ��d�v�ƍl���Ă��܂��B