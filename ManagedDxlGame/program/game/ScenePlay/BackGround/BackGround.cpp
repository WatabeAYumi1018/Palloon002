#include "BackGround.h"
#include "../../ScenePlay/Camera/Camera.h"


BackGround::BackGround() : GameObject(tnl::Vector3{ 0,0,0 })
{

}

void BackGround::Draw(float delta_time, const Camera* camera)
{
	tnl::Vector3 draw_pos
		= m_pos - (camera->GetTarget() * m_scroll_speed)
		+ tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

	DrawRotaGraph(draw_pos.x, draw_pos.y, 1.0f, 0, m_stage_hdl, true);
}

void BackGround::SetBackground(const std::string& backgroundPath)
{
	if (m_stage_hdl != -1)
	{
		DeleteGraph(m_stage_hdl);
	}
	m_stage_hdl = LoadGraph(backgroundPath.c_str());
}
