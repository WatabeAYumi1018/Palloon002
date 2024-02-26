#include "../../dxlib_ext/dxlib_ext.h"
#include "SceneTitle.h"
#include "../sceneSelect/SceneSelect.h"
#include "../../engine/SceneManager.h"
#include "../SceneAll/Music/MusicManager.h"

void SceneTitle::Update(float delta_time) 
{
	m_sequence.update(delta_time);
	
	LogoHandle(delta_time);
	
	BoundHandle(delta_time);

	m_balloon_spawn_timer += delta_time;

	if (m_balloon_spawn_timer >= SPAWN_INTERVSL)
	{
		m_balloon_spawn_timer = 0.0f; // タイマーをリセット
	}

	for (auto& balloon : balloons)
	{
		balloon.Update(delta_time);
	}
}

void SceneTitle::Draw(float delta_time) 
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

	for (const auto& balloon : balloons)
	{
		DrawExtendGraph
		(
			balloon.GetPos().x
			, balloon.GetPos().y
			,balloon.GetPos().x + balloon.GetSize()
			,balloon.GetPos().y + balloon.GetSize()
			, balloon.GetHdl()
			, TRUE
		);
	}

	int logo_height;
	
	GetGraphSize(m_logo_hdl, NULL, &logo_height); 
	
	DrawRectExtendGraph
	(
		300
		, 400
		, 400 + m_current_width
		, 400 + logo_height
		, 0
		, 0
		, m_current_width
		, logo_height
		, m_logo_hdl
		, TRUE
	);
	
	DrawGraph(400, m_chara_pos.y, m_palloon_hdl, TRUE);
}

bool SceneTitle::SeqIdle(float delta_time) 
{
	if (m_sequence.isStart())
	{
		MusicManager::GetInstance()
			.LoadBGM("music/title.mp3");
	
		MusicManager::GetInstance()
			.LoadSE("start","music/pushStart.wav");

		m_back_hdl 
			= LoadGraph("graphics/title/title.png");
		
		m_logo_hdl 
			= LoadGraph("graphics/title/TitleLogo.png");
		
		m_palloon_hdl
			= LoadGraph("graphics/title/PALLOON.png");
		
		SpawnBalloon();

		MusicManager::GetInstance().PlayBGM();

		m_current_width = 0;
	}

	if 
		(
			tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) 
			|| tnl::Input::IsPadDownTrigger(ePad::KEY_1)
		)
	{
		MusicManager::GetInstance().PlaySE("start");

		auto scene = SceneManager::GetInstance();
		
		scene->ChangeScene(new SceneSelect());
	}
	return true;
}

void SceneTitle::LogoHandle(float delta_time)
{
	// ロゴの幅を徐々に増やす
	m_current_width += DISPLAY_TIME * delta_time * 5;

	// ロゴの幅が画面幅を超えたら画面幅に固定
	if (m_current_width > DXE_WINDOW_WIDTH) 
	{
		m_current_width = DXE_WINDOW_WIDTH;

		// ロゴの描画終了でのフラグを設定
		if (!m_is_logo_displayed) 
		{
			m_is_logo_displayed = true;  
		}
	}
}

void SceneTitle::BoundHandle(float delta_time)
{
	// ロゴが完全に表示されてからキャラをバウンドさせる
	if (!m_is_logo_displayed) return;

	if (m_bound_count < MAX_BOUNDE)
	{
		// 重力を速度に加える
		m_velocity.y += m_gravity.y; 
		// 速度を位置に加える
		m_chara_pos.y += m_velocity.y; 

		// イラストが地面に到達したらバウンドさせる
		if (m_chara_pos.y >= GROUND_Y)
		{
			// 位置を地面に設定
			m_chara_pos.y = GROUND_Y; 
			// バウンドさせるために速度を反転&減少させる
			m_velocity.y *= BOUND_RATE; 
			// バウンド回数を増やす
			m_bound_count++; 
		}
	}
	else
	{
		// 最大バウンド回数を超えた場合、イラストを画面中央に固定する
		m_chara_pos.y = GROUND_Y;
	}
}

void SceneTitle::SpawnBalloon() 
{
	for (int i = 0; i < BALLOON_SPAWN; ++i)
	{
		// 複数のバルーンをスポーン
		balloons.emplace_back(); 
	}
}

void SceneTitle::Finalize()
{
	DeleteGraph(m_back_hdl);

	DeleteGraph(m_logo_hdl);
	
	DeleteGraph(m_palloon_hdl);

	balloons.clear();
}