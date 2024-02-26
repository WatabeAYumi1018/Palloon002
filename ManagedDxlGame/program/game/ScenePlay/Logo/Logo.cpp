#include "Logo.h"

Logo::Logo() :GameObject({DXE_WINDOW_WIDTH>>1,DXE_WINDOW_HEIGHT>>1,0})
{
	m_clear_botton_hdl 
		= LoadGraph("graphics/logo/clear_botton.png");

	m_clear_logo_hdl
		= LoadGraph("graphics/logo/clear_logo.png");

	m_burst_logo_hdl 
		= LoadGraph("graphics/logo/burst_logo.png");

	m_fall_logo_hdl 
		= LoadGraph("graphics/logo/fall_logo.png");
}

Logo::~Logo()
{
	DeleteGraph(m_clear_botton_hdl);

	DeleteGraph(m_clear_logo_hdl);

	DeleteGraph(m_burst_logo_hdl);

	DeleteGraph(m_fall_logo_hdl);
}

void Logo::Update(float delta_time)
{
	if (m_is_clear)
	{
		//“_–Å•\Ž¦
		m_blink_elapsed_time += delta_time;

		if (m_blink_elapsed_time > BLINK_ELAPSED_TIME)
		{
			m_is_draw = !m_is_draw;

			m_blink_elapsed_time = 0.0f;
		}
	}
}

void Logo::Draw(float delta_time, const Camera* camera)
{
	if (m_is_draw)
	{
		DrawGraph
		(
			m_pos.x - m_botton_size
			, m_pos.y + m_result_y_size
			, m_clear_botton_hdl
			, TRUE
		);
	}

	switch (e_logo_type)
	{
	case eLogoType::Clear:

		DrawGraph
		(
			m_pos.x- m_result_x_size
			, m_pos.y - m_result_y_size
			, m_clear_logo_hdl
			, TRUE
		);

		break;

	case eLogoType::Burst:

		DrawGraph
		(
			m_pos.x - m_result_x_size
			, m_pos.y - m_result_y_size
			, m_burst_logo_hdl
			, TRUE
		);

		break;

	case eLogoType::Fall:

		DrawGraph
		(
			m_pos.x - m_result_x_size
			, m_pos.y - m_result_y_size
			, m_fall_logo_hdl
			, TRUE
		);

		break;
	}
}