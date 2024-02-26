#include "Character.h"

Character::Character
(
	const tnl::Vector3 pos
	,int size
	, int hp
	, const tnl::Vector3 velocity
) 
	:GameObject(pos)
	, m_size(size)
	, m_hp(hp)
	, m_velocity(velocity)
{
	// CSV����A�j���[�V�����f�[�^�����[�h
	m_animLoader
		= new wta::DrawAnim("csv/AnimLoad.csv", "graphics/animation");
}

Character::~Character()
{
	delete m_animLoader;

	m_animLoader = nullptr;
}

void Character::DecreaseHP(int damage)
{
	m_hp-=damage;

	if (m_hp <= 0)
	{
		m_is_dead = true;
	}
}


void Character::Invincible(float delta_time)
{
	// ���G���Ԃ��X�V
	if (m_is_invincible)
	{
		m_invincible_time += delta_time;

		if (m_invincible_time >= 5.0f)
		{
			m_is_invincible = false;
		}
	}
}

//���G���Ԃ̃��Z�b�g
void Character::MakeInvincible()
{
	m_is_invincible = true;

	m_invincible_time = 0.0f;
}
