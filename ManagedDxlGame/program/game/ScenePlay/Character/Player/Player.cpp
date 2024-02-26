#include "Player.h"
#include "../../../SceneAll/Music/MusicManager.h"
#include "../../Camera/Camera.h"
#include "../../Collision/Collision.h"
#include "../../Wind/Wind.h"
#include "../../Map/Map.h"
#include "../../Logo/Logo.h"

//キャラクターの初期化子
Player::Player
(
	const tnl::Vector3& initialPos
	, Collision* collision
	, Map* map
	,Wind* wind
	, Logo* logo
)
	:Character(initialPos, SIZE,MAX_HP,{ VELOCITY_X, VELOCITY_Y,0 })
	,m_collision(collision)
	, m_map(map)
	,m_wind(wind)
	,m_logo(logo)
{

}

void Player::Update(float delta_time)
{
	if (m_hp <= 0)
	{
		m_is_draw = false;
	}

	if (!m_is_draw)
	{
		m_logo->SetIsClear(true);

		m_logo->SetLogoState(eLogoType::Burst);

		return;
	}

	m_is_ground = CheckIsGround();

	Gravity(delta_time);

	ApplyWind(delta_time);

	MoveRange();

	ActionHandle(delta_time);

	Invincible(delta_time);
}

void Player::Draw(float delta_time, const Camera* camera)
{
	//描画しない場合は終了
	if (!m_is_draw)
	{
		return;
	}

	if (m_is_draw)
	{
		tnl::Vector3 draw_pos
			=m_pos - camera->GetTarget() 
			+ tnl::Vector3(DXE_WINDOW_WIDTH >> 1, DXE_WINDOW_HEIGHT >> 1, 0);

		//無敵中は点滅描画
		if (m_is_invincible)
		{
			// 0.1秒ごとに表示・非表示を切り替えて点滅
			if (static_cast<int>(m_invincible_time * 10) % 2 == 0)
			{
				m_animLoader->Draw(delta_time, draw_pos);
			}
		}
		else
		{
			m_animLoader->Draw(delta_time, draw_pos);
		}
	}
}

void Player::StampAction(float delta_time)
{	
	if (m_is_direction_right)
	{
		e_currentAction = ePlayerAction::Stamp_right;
	}
	else
	{
		e_currentAction = ePlayerAction::Stamp_left;
	}

	m_stamp_time += delta_time;

	//スタンプアクション終了につきリセット
	if (m_stamp_time >= STAMP_TIME)
	{
		m_stamp_time = 0.0f; 

		m_is_stamp = false;

		m_is_hovering = false;
	}
}

void Player::RollAction(float delta_time)
{
	if (m_is_direction_right)
	{
		e_currentAction = ePlayerAction::Roll_right;
	}
	else
	{
		e_currentAction = ePlayerAction::Roll_left;
	}
}

//アニメーション設定
void Player::ActionHandle(float delta_time)
{
	MoveHandle(delta_time);

	switch (e_currentAction)
	{
	case ePlayerAction::Move_right:

		m_animLoader->SetAnimation(2);  

		break;
	
	case ePlayerAction::Move_left:
		
		m_animLoader->SetAnimation(3);  
		
		break;

	case ePlayerAction::Dash_right:
	
		m_animLoader->SetAnimation(4); 
	
		break;
	
	case ePlayerAction::Dash_left:

		m_animLoader->SetAnimation(5);  

		break;

	case ePlayerAction::Idle_right:

		m_animLoader->SetAnimation(0); 

		break;

	case ePlayerAction::Idle_left:

		m_animLoader->SetAnimation(1);  

		break;

	case ePlayerAction::Hover_right:

		m_animLoader->SetAnimation(6);  

		break;

	case ePlayerAction::Hover_left:

		m_animLoader->SetAnimation(7);  

		break;

	case ePlayerAction::Hover_end_right:

		m_animLoader->SetAnimation(8); 

		break;

	case ePlayerAction::Hover_end_left:

		m_animLoader->SetAnimation(9);  

		break;

	case ePlayerAction::Stamp_right:

		m_animLoader->SetAnimation(10);  

		break;

	case ePlayerAction::Stamp_left:

		m_animLoader->SetAnimation(11);  

		break;

	case ePlayerAction::Roll_right:
		
		m_animLoader->SetAnimation(12);  

		break;

	case ePlayerAction::Roll_left:

		m_animLoader->SetAnimation(13); 

		break;

	case ePlayerAction::Fire_right:

		m_animLoader->SetAnimation(14);  

		break;

	case ePlayerAction::Fire_left:

		m_animLoader->SetAnimation(15); 

		break;

	case ePlayerAction::Beam_right:

		m_animLoader->SetAnimation(16); 

		break;

	case ePlayerAction::Beam_left:

		m_animLoader->SetAnimation(17);  

		break;

	default:

		break;
	}
}

//ボタン処理
void Player::MoveHandle(float delta_time)
{
	m_is_rolling = false;

	//アナログスティックの入力値を取得
	GetJoypadAnalogInput(&m_input_x, &m_input_y, DX_INPUT_PAD1);

	//デフォルト検知が-1000～1000のため、-1.0～1.0に正規化
	m_normalized_input_x = m_input_x / 1000.0f;

	//ジャンプボタン、または接地判定falseの場合、ジャンプ処理を行う
	if (
			(tnl::Input::IsKeyDown(eKeys::KB_SPACE) 
			||tnl::Input::IsPadDown(ePad::KEY_3))
			|| !CheckIsGround()
		)
	{
		m_is_hovering = true;
	}

	if (m_is_hovering && m_stamp_time == 0.0f)
	{
		Hovering(delta_time);

		HoveringDirection(delta_time);
	}

	if (m_is_stamp)
	{
		StampAction(delta_time);
	}

	if 
		(
			tnl::Input::IsKeyDown(eKeys::KB_C) 
			|| tnl::Input::IsPadDown(ePad::KEY_1)
		)
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Beam_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Beam_left;
		}
	}

	else if
		(
			tnl::Input::IsKeyDown(eKeys::KB_X) 
			|| tnl::Input::IsPadDown(ePad::KEY_0)
		)
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Fire_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Fire_left;
		}
	}

	//地上にいる場合
	if (CheckIsGround())
	{
		if 
			(
				tnl::Input::IsKeyDown(eKeys::KB_RIGHT) 
				|| m_normalized_input_x > 0
			)
		{
			m_is_direction_right = true;
	
			if 
				(
					tnl::Input::IsKeyDown(eKeys::KB_LSHIFT) 
					|| m_normalized_input_x > DASH_THRESHOLD
				)
			{
				m_pos.x += VELOCITY_X * delta_time * 2;

				e_currentAction = ePlayerAction::Dash_right;

				//ダッシュ中にCで転がる攻撃
				if
					(
						tnl::Input::IsKeyDown(eKeys::KB_Z) 
						|| tnl::Input::IsPadDown(ePad::KEY_2)
					)
				{
					m_is_rolling = true;

					RollAction(delta_time);
				}
			}
			else
			{
				m_pos.x += VELOCITY_X * delta_time;

				e_currentAction = ePlayerAction::Move_right;
			}
		}
		else if 
			(
				tnl::Input::IsKeyDown(eKeys::KB_LEFT) 
				|| m_normalized_input_x < 0
			)
		{
			m_is_direction_right = false;

			if 
				(
					tnl::Input::IsKeyDown(eKeys::KB_LSHIFT)
					|| abs(m_normalized_input_x) > DASH_THRESHOLD
				)
			{
				m_pos.x -= VELOCITY_X * delta_time * 2.0f;

				e_currentAction = ePlayerAction::Dash_left;

				//ダッシュ中にCで転がる攻撃
				if 
					(
						tnl::Input::IsKeyDown(eKeys::KB_Z) 
						|| tnl::Input::IsPadDown(ePad::KEY_2)
					)
				{
					m_is_rolling = true;

					RollAction(delta_time);
				}
			}
			else
			{
				m_pos.x -= VELOCITY_X * delta_time;

				e_currentAction = ePlayerAction::Move_left;
			}
		}
		else if 
			(
				tnl::Input::IsKeyDown(eKeys::KB_C) 
				|| tnl::Input::IsPadDown(ePad::KEY_1)
			)
		{

			if (m_is_direction_right)
			{
				e_currentAction = ePlayerAction::Beam_right;
			}
			else
			{
				e_currentAction = ePlayerAction::Beam_left;
			}
		}
		else if 
			(
				tnl::Input::IsKeyDown(eKeys::KB_X) 
				|| tnl::Input::IsPadDown(ePad::KEY_0)
			)
		{

			if (m_is_direction_right)
			{
				e_currentAction = ePlayerAction::Fire_right;
			}
			else
			{
				e_currentAction = ePlayerAction::Fire_left;
			}
		}
		else
		{
			if (m_is_direction_right)
			{
				e_currentAction = ePlayerAction::Idle_right;
			}
			else
			{
				e_currentAction = ePlayerAction::Idle_left;
			}
		}
	}
}

//接地判定
bool Player::CheckIsGround()
{
	if (m_is_dead)
	{
		return false;
	}

	//足元の座標を取得
	tnl::Vector3 foot_pos = m_pos + tnl::Vector3(0, 50, 0);

	tnl::Vector3 chip_pos 
		= m_collision->GetCharacterMapChipPos(foot_pos, m_map);

	sCollisionInfo foot_collision
		= m_map->GetCollisionInfo()[chip_pos.y][chip_pos.x];

	//足元が地面か判定
	return 
		(
			foot_collision.s_type == eMapCollisionType::Box 
			||foot_collision.s_type == eMapCollisionType::Line
		);
}

void Player::MoveRange()
{
	//プレイヤーの移動範囲を制限
	if (m_pos.x < SIZE)
	{
		m_pos.x = SIZE;
	}
	if (m_pos.x > (m_map -> GetMapChipX() * m_map->MAP_CHIP_SIZE - SIZE))
	{
		m_pos.x = m_map->GetMapChipX()* m_map->MAP_CHIP_SIZE - SIZE;
	}
	if (m_pos.y < SIZE)
	{
		m_pos.y = SIZE;
	}
	if (m_pos.y >= (m_map->GetMapChipY() * m_map->MAP_CHIP_SIZE - 55))
	{
		m_is_dead=true;

		m_logo->SetIsClear(true);

		m_logo->SetLogoState(eLogoType::Fall);
	}
}

void Player::Gravity(float delta_time)
{
	//重力で下に落ちる
	if (m_is_hovered)
	{
		//空気が抜けたら落下時の重力2倍
		m_pos.y += 2 * m_gravity.y * delta_time;    
	}
	else
	{
		m_pos.y += m_gravity.y * delta_time;
	}
}

void Player::ApplyWind(float delta_time)
{
	float wind_strength = m_wind->GetWindStrength();

	if (m_pos.y < 5000)
	{
		float depthEffect = ( m_pos.y - 5000) / 10.0f;

		m_pos.x 
			+= m_wind->GetDirection()
			* wind_strength 
			* depthEffect 
			* delta_time;
	}
}

void Player::Hovering(float delta_time)
{
	if (m_is_ground)
	{
		//地面にいるときは浮遊力をリセット
		m_hovering_force = HOVER_FIRST_FORCE; 
	}
	if (m_hovering_force > 0)
	{
		//浮遊力に基づいて位置を更新
		m_pos.y -= m_hovering_force * VELOCITY_Y * delta_time; 
		//浮遊力を減少
		m_hovering_force -= HOVER_DECAY_FORCE * delta_time;
		// 0以下にはならないようにする
		m_hovering_force = max(m_hovering_force, 0.0f); 
	}
	else
	{
		m_hovering_force = 0.0f; 

		m_is_hovering = false;

		m_is_hovered = false;
	}
}

void Player::HoveringDirection(float delta_time)
{
	// ホバリング中
	if (m_hovering_force > 0)
	{
		if (m_is_direction_right)
		{
			HoveringStartRight(delta_time);
		}
		else
		{
			HoveringStartLeft(delta_time);
		}
	}
	//下降中
	else
	{
		if (m_is_direction_right)
		{
			HoveringStartRight(delta_time);
		}
		else
		{
			HoveringStartLeft(delta_time);
		}
	}
}

void Player::HoveringStartRight(float delta_time)
{
	if 
		(
			tnl::Input::IsKeyDown(eKeys::KB_RIGHT)
			|| m_normalized_input_x > 0
		)
	{
		m_is_direction_right = true;

		e_currentAction = ePlayerAction::Hover_right;

		m_pos.x += VELOCITY_X * delta_time;
	}
	else if 
		(
			tnl::Input::IsKeyDown(eKeys::KB_LEFT) 
			|| m_normalized_input_x < 0
		)
	{
		m_is_direction_right = false;

		e_currentAction = ePlayerAction::Hover_left;

		m_pos.x -= VELOCITY_X * delta_time;
	}
	else
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Hover_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Hover_left;
		}
	}
}

void Player::HoveringStartLeft(float delta_time)
{
	if 
		(
			tnl::Input::IsKeyDown(eKeys::KB_LEFT) 
			|| m_normalized_input_x < 0
		)
	{
		m_is_direction_right = false;

		e_currentAction = ePlayerAction::Hover_left;

		m_pos.x -= VELOCITY_X * delta_time;
	}
	else if 
		(
			tnl::Input::IsKeyDown(eKeys::KB_RIGHT) 
			|| m_normalized_input_x > 0
		)
	{
		m_is_direction_right = true;

		e_currentAction = ePlayerAction::Hover_right;

		m_pos.x += VELOCITY_X * delta_time;
	}
	else
	{
		if (m_is_direction_right)
		{
			e_currentAction = ePlayerAction::Hover_right;
		}
		else
		{
			e_currentAction = ePlayerAction::Hover_left;
		}
	}
}


