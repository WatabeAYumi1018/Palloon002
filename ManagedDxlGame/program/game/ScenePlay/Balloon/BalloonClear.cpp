#include "BalloonClear.h"
#include "../../SceneAll/Music/MusicManager.h"
#include "../Character/Player/Player.h"
#include "../Collision/Collision.h"
#include "../Camera/Camera.h"


BalloonClear::BalloonClear(Collision* collision)
	:GameObject(tnl::Vector3{ 0,0,0 })
	, m_collision(collision)
{
	Initialize();
}

void BalloonClear::Initialize()
{
	m_balloon_hdl
		= LoadGraph("graphics/balloon/clear_balloon.png");

	m_balloon_clear_hdl
		= LoadGraph("graphics/balloon/clear_palloon.png");

	m_clear_up_hdl
		= LoadGraph("graphics/logo/clear_up.png");
}

void BalloonClear::Update(float delta_time)
{
	if (m_is_draw)
	{
		ClearPosChange();

		if (m_pos.x != 0 && m_pos.y != 0)
		{
			MoveBalloon(delta_time);
		}
	}
}

void BalloonClear::Draw(float delta_time, const Camera* camera)
{
	if (m_is_draw)
	{
		//ClearPosChange();

		tnl::Vector3 draw_pos
			= m_pos - camera->GetTarget() 
			+ tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

		if (m_pos.x != 0 && m_pos.y != 0 && m_collision->GetIsUp())
		{
			// 原因は分かりませんが、コントローラの十字を条件に加えると
			// ボタンを押していないのにも関わらず、ボタンが押された状態になります。
			if
			(
				m_collision->GetIsClear()
				&& tnl::Input::IsKeyDown(eKeys::KB_UP)
			)
			{
				m_is_change_grahic = true;
			}

			if (m_is_change_grahic)
			{
				DrawExtendGraph
				(
					draw_pos.x - m_size.x
					, draw_pos.y - m_size.y
					, draw_pos.x + m_size.x
					, draw_pos.y
					, m_balloon_clear_hdl
					, true
				);

				e_balloon_state = eBalloonState::ClearRising;
			}
			else
			{
				DrawExtendGraph
				(
					draw_pos.x - m_size.x
					, draw_pos.y - m_size.y
					, draw_pos.x + m_size.x
					, draw_pos.y
					, m_balloon_hdl
					, true
				);
			}
		}

		if 
		(
			e_balloon_state == eBalloonState::Floating
			&& m_blink_time < (BLINK_INTERVAL / 2.0f)
		)
		{
			DrawGraph(draw_pos.x - 100, draw_pos.y, m_clear_up_hdl, true);
		}
	}
}

void BalloonClear::ClearPosChange()
{
	tnl::Vector3 clear_pos = m_collision->GetClearPos();

	tnl::Vector3 default_pos = { 0,0,0 };

	if (clear_pos.x != default_pos.x && clear_pos.y != default_pos.y)
	{
		m_target_pos = clear_pos;

		if (e_balloon_state == eBalloonState::Hidden)
		{
			e_balloon_state = eBalloonState::Rising;

			m_pos = { m_target_pos.x, DXE_WINDOW_HEIGHT + 1000, 0 };
		}
	}
}

void BalloonClear::MoveBalloon(float delta_time)
{
	switch (e_balloon_state)
	{
	case eBalloonState::Rising:

		m_pos.y -= delta_time * m_velocity_y;

		if (m_pos.y <= m_target_pos.y)
		{
			m_pos.y = m_target_pos.y;

			e_balloon_state = eBalloonState::Floating;
		}

		break;

	case eBalloonState::Floating:

		m_float_time += delta_time;

		m_offset_y = sin(m_float_time) * 10.0f;

		m_pos.y = m_target_pos.y + m_offset_y;

		//ボタンの点滅描画
		m_blink_time += delta_time;

		if (m_blink_time > BLINK_INTERVAL)
		{
			m_blink_time = 0.0f;
		}

		break;

	case eBalloonState::ClearRising:

		m_pos.y -= delta_time * m_velocity_y;

		break;

	default:

		break;
	}
}

void BalloonClear::Finalize()
{
	DeleteGraph(m_balloon_hdl);

	DeleteGraph(m_balloon_clear_hdl);
}