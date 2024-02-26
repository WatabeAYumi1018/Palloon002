#include "../Character/Player/Player.h"
#include "../Character/Enemy/Enemy.h"
#include "UI.h"

UI::UI(Player* player, Enemy* enemy)
	: GameObject(tnl::Vector3{ 10,500,0 })
	, m_player(player)
	, m_enemy(enemy)
{
	Initialize();
}

void UI::Initialize()
{
	m_hp_player_hdl 
		=LoadGraph("graphics/balloon/balloon_hp_player.png");

	m_hp_boss_hdl 
		=LoadGraph("graphics/balloon/balloon_hp_boss.png");
}

void UI::Draw(float delta_time, const Camera* camera)
{
	HpPlayerBalloons();

	if (m_is_draw)
	{
		HpBossBallons();
	}
}

void UI::HpPlayerBalloons()
{
	if (!m_player)
	{
		return;
	}

	int current_hp = m_player->GetHp();

	for (int i = 0; i < current_hp; i++)
	{
		DrawExtendGraph
		(
			0 + (i * BALLON_WIDTH)
			, BALLON_PLAYER_START_Y
			, BALLON_INTERVAL_PLAYER + (i * BALLON_WIDTH)
			, BALLON_PLAYER_END_Y
			, m_hp_player_hdl
			, TRUE
		);
	}
}

void UI::HpBossBallons()
{
	if (!m_enemy)
	{
		return;
	}

	int current_hp = m_enemy->GetHp();

	for (int i = 0; i < current_hp; i++)
	{
		DrawExtendGraph
		(
			0 + (i * BALLON_WIDTH)
			, 0
			, BALLON_INTERVAL_BOSS + (i * BALLON_WIDTH)
			, BALLON_BOSS_END_Y
			, m_hp_boss_hdl
			, TRUE
		);
	}
}
