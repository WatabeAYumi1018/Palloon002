#include "Effect.h"
#include "../Character/Character.h"

Effect::Effect(tnl::Vector3 pos, Character* character) 
	:GameObject(pos), m_character(character)
{
	m_animLoader 
		= new wta::DrawAnim("csv/AnimLoad.csv", "graphics/animation");
}

Effect::~Effect()
{
	delete m_animLoader;

	m_animLoader = nullptr;
}