#include "../../dxlib_ext/dxlib_ext.h"
#include "SceneSelect.h"
#include "../ScenePlay/scenePlay.h"
#include "../../engine/SceneManager.h"


SceneSelect::SceneSelect() : m_selected_stage(0)
{
	m_stage_names.emplace_back("stage1");
	
	m_stage_names.emplace_back("stage2");
	
	m_stage_names.emplace_back("stage3");
	
	m_stage_names.emplace_back("stageBoss");
};

void SceneSelect::Update(float delta_time)
{
	m_sequence.update(delta_time);

	MoveBalloon(delta_time);
}

void SceneSelect::Draw(float delta_time)
{
	DrawExtendGraph
	(
		0
		, 0
		, DXE_WINDOW_WIDTH
		, DXE_WINDOW_HEIGHT
		, m_back_hdl
		, TRUE
	);

	DrawGraph
	(
		50
		, 100 + (m_selected_stage == 0 ? m_balloon_offset_y : 0)
		, m_stage1_hdl
		, TRUE
	);

	DrawGraph
	(
		350
		, 300 + (m_selected_stage == 1 ? m_balloon_offset_y : 0)
		, m_stage2_hdl
		, TRUE
	);

	DrawGraph
	(
		650
		, 100 + (m_selected_stage == 2 ? m_balloon_offset_y : 0)
		, m_stage3_hdl
		, TRUE
	);

	DrawGraph
	(
		950
		, 300 + (m_selected_stage == 3 ? m_balloon_offset_y : 0)
		, m_boss_hdl
		, TRUE
	);
}

bool SceneSelect::SeqIdle(float delta_time)
{
	if (m_sequence.isStart())
	{
		MusicManager::GetInstance()
			.LoadSE("select", "music/selectBottan.wav");

		MusicManager::GetInstance()
			.LoadSE("start", "music/pushStart.wav");

		m_back_hdl   = LoadGraph("graphics/title/title.png");

		m_stage1_hdl = LoadGraph("graphics/select/stage1.png");

		m_stage2_hdl = LoadGraph("graphics/select/stage2.png");

		m_stage3_hdl = LoadGraph("graphics/select/stage3.png");

		m_boss_hdl   = LoadGraph("graphics/select/stage_boss.png");
	}

	if 
		(
			tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) 
			|| tnl::Input::IsPadDownTrigger(ePad::KEY_1)
		)
	{
		MusicManager::GetInstance().PlaySE("start");

		auto scene = SceneManager::GetInstance();
		//選んだステージによって切り替える
		scene->ChangeScene(new ScenePlay(GetSelectedStage()));
	}
	return true;
}

void SceneSelect::MoveBalloon(float delta_time)
{
	//クールダウンの更新
	//アナログスティックの感知による過剰入力を防ぐ（ある程度の力は無視）
	if (m_input_cooldown_time > 0.0f)
	{
		m_input_cooldown_time -= delta_time;
	}

	GetJoypadAnalogInput(&m_input_x, &m_input_y, DX_INPUT_PAD1);
	
	m_normalized_input_x = m_input_x / 1000.0f;

	// キー入力の処理
	if (m_input_cooldown_time <= 0.0f)
	{
		if 
			(
				(tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT) 
					|| (m_normalized_input_x > DEADZONE 
						&& m_previous_input_x <= DEADZONE)
				)
			)
		{
			MusicManager::GetInstance().PlaySE("select");

			m_selected_stage = (m_selected_stage + 1) % STAGE_NUM;

			m_input_cooldown_time = INPUT_COUNTDOWN_TIME;
		}
		else if 
			(
				(tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT) 
					|| (m_normalized_input_x < -DEADZONE 
						&& m_previous_input_x >= -DEADZONE)
				)
			)
		{
			MusicManager::GetInstance().PlaySE("select");

			m_selected_stage 
				= (m_selected_stage - 1 + STAGE_NUM) % STAGE_NUM;

			m_input_cooldown_time = INPUT_COUNTDOWN_TIME;
		}
	}

	m_previous_input_x = m_normalized_input_x;

	//風船の動きの速さを調整
	m_balloon_time += delta_time * m_balloon_velocity_y; 

	// sin関数を使用して風船の上下のオフセットを計算
	m_balloon_offset_y = sin(m_balloon_time) * 10.0f;
}

void SceneSelect::Finalize()
{
	DeleteGraph(m_back_hdl);

	DeleteGraph(m_stage1_hdl);

	DeleteGraph(m_stage2_hdl);

	DeleteGraph(m_stage3_hdl);

	DeleteGraph(m_boss_hdl);

}