#include "../../wta_library/wta_IsIntersectCalc.h"
#include "../../dxlib_ext/dxlib_ext.h"
#include "../ScenePlay/Character/Enemy/EnemyLoad.h"
#include "../ScenePlay/Collision/Collision.h"
#include "../ScenePlay/Character/Player/Player.h"
#include "../ScenePlay/Character/Enemy/Enemy.h"
#include "../ScenePlay/Character/Enemy/EnemySlim.h"
#include "../ScenePlay/Character/Enemy/EnemyPlant.h"
#include "../ScenePlay/Character/Enemy/EnemyBird.h"
#include "../ScenePlay/Character/Enemy/EnemyMasician.h"
#include "../ScenePlay/Character/Enemy/EnemyFairy.h"
#include "../ScenePlay/Character/Enemy/EnemyDoragon.h"
#include "../ScenePlay/Effect/EffectPlayer.h"
#include "../ScenePlay/Effect/EffectBoss.h"
#include "../ScenePlay/Camera/Camera.h"
#include "../SceneSelect/SceneSelect.h"
#include "../SceneTitle/SceneTitle.h"
#include "../../engine/SceneManager.h"
#include "../ScenePlay/BackGround/BackGround.h"
#include "../SceneAll/Balloon/Balloon.h"
#include "../ScenePlay/Balloon/BalloonInstruction.h"
#include "../ScenePlay/Balloon/BalloonClear.h"
#include "../ScenePlay/Wind/Wind.h"
#include "../ScenePlay/Logo/Logo.h"
#include "../ScenePlay/Map/Map.h"
#include "../ScenePlay/UI/UI.h"
#include "ScenePlay.h"


ScenePlay::ScenePlay(const std::string& stageName) : m_stage_name(stageName)
{
	Initialize();
}

void ScenePlay::Initialize()
{
	m_camera=new Camera();

	m_collision = new Collision();

	m_backGround=new BackGround();

	m_balloonInstruction = new BalloonInstruction();

	m_balloonClear = new BalloonClear(m_collision);

	m_map = new Map(m_stage_name);

	m_wind = new Wind();

	m_logo = new Logo();

	m_backGround->SetBackground(m_map->GetCurrentStageInfo().s_background_hdl);
	
	tnl::Vector3 player_init_pos 
		= m_map->GetCurrentStageInfo().s_initial_player_pos;	
	
	m_player 
		= new Player(player_init_pos, m_collision, m_map, m_wind,m_logo);

	m_effectPlayer_beam
		= new EffectPlayer(m_player, eEffectPlayerType::Beam);

	m_effectPlayer_fire 
		= new EffectPlayer(m_player, eEffectPlayerType::Fire);

	//�v���C�V�[���ɕK�v��Object��ǂݍ��݁A����������
	m_gameObjects.emplace_back(new Balloon());

	InitEnemy();

	m_gameObjects.emplace_back(m_player);

	m_gameObjects.emplace_back(m_effectPlayer_beam);

	m_gameObjects.emplace_back(m_effectPlayer_fire);

	m_gameObjects.emplace_back(m_balloonClear);
	
	m_effectBoss = new EffectBoss(m_enemy,m_player);

	m_gameObjects.emplace_back(m_effectBoss);

	m_ui = new UI(m_player, m_enemy);	

	m_gameObjects.emplace_back(m_ui);

	m_gameObjects.emplace_back(m_logo);
}

void ScenePlay::InitMusic()
{
	// �X�e�[�W������BGM�̃p�X���擾
	std::string bgmPath = "";

	for (const auto& stageInfo : m_map->GetStageList())
	{
		if (stageInfo.s_stage_name == m_stage_name)
		{
			bgmPath = stageInfo.s_music_bgm;

			break;
		}
	}

	// BGM�̃��[�h�ƍĐ�
	if (!bgmPath.empty())
	{
		MusicManager::GetInstance().LoadBGM(bgmPath);

		MusicManager::GetInstance().PlayBGM();
	}

	// SE�̃��[�h
	MusicManager::GetInstance()
		.LoadSE("dead", "music/rollHit.mp3");

	MusicManager::GetInstance()
		.LoadSE("fire", "music/PlayerFire.wav");

	MusicManager::GetInstance()
		.LoadSE("beam", "music/playerBeam.wav");

	MusicManager::GetInstance()
		.LoadSE("enter", "music/pushStart.wav");

	MusicManager::GetInstance()
		.LoadSE("clear", "music/clear.wav");
}

void ScenePlay::InitEnemy()
{
	m_enemy_infos 
		= m_enemyLoad->LoadEnemyInfo("csv/EnemyLoad.csv");

	auto dataList
		= m_enemyLoad->LoadEnemyData(m_map->GetCurrentStageInfo().s_enemy_csv);

	for (auto& data : dataList)
	{
		switch (data.s_type_id)
		{
		case 0:
			
			m_enemy = new EnemySlim
						(
							data
							, m_enemy_infos[data.s_type_id]
							, m_player,m_map,m_collision
							, m_camera
						);
			
			break;

		case 1:
			
			m_enemy = new EnemyPlant
						(
							data
							, m_enemy_infos[data.s_type_id]
							, m_player, m_map, m_collision
							, m_camera
						);
			break;

		case 2:
			
			m_enemy = new EnemyMasician
						(
							data
							, m_enemy_infos[data.s_type_id]
							, m_player, m_map, m_collision
							, m_camera
						);

			break;

		case 3:
			
			m_enemy = new EnemyFairy
						(
							data
							, m_enemy_infos[data.s_type_id]
							, m_player, m_map, m_collision
							, m_camera
						);

			if (m_stage_name == "stage3")
			{
				static_cast<EnemyFairy*>(m_enemy)->RandomType();
			}

			break;

		case 4:
			
			m_enemy = new EnemyBird
						(
							data
							, m_enemy_infos[data.s_type_id]
							, m_player, m_map, m_collision
							, m_camera
						);

			break;

		case 5:
					
			m_enemy = new EnemyDoragon
						(
							data
							, m_enemy_infos[data.s_type_id]
							, m_player, m_map, m_collision
							, m_camera
						);

			break;

		// ������ID�̏ꍇ�̓X�L�b�v
		default:
			
			continue;
		}

		m_enemies.emplace_back(m_enemy);

		m_gameObjects.emplace_back(m_enemy);
	}
}

void ScenePlay::Update(float delta_time)
{	
	m_collision->CollisionCalculate(m_player, m_map, 10);

	m_camera->Update(delta_time, m_player, m_map);

	m_map->LoadMapCollision();

	CollisionCheck(delta_time);

	if (m_stage_name == "stage1")
	{
		m_balloonClear->SetIsDraw(true);

		m_balloonInstruction->Update(delta_time);
	}
	
	if (m_stage_name == "stage2")
	{
		m_balloonClear->SetIsDraw(true);

		m_wind->Update(delta_time);
	}

	if (m_stage_name == "stage3")
	{
		CreateEnemy(delta_time);

		if (m_enemy_respawn_count >= ENEMY_TOTAL_RESPAWNS)
		{
			m_balloonClear->SetIsDraw(true);

			m_balloonInstruction->Update(delta_time);
		}
	}

	if (m_stage_name == "stageBoss")
	{
		if (m_enemy->GetIsDead())
		{
			m_balloonClear->SetIsDraw(true);

			m_balloonInstruction->Update(delta_time);
		}
	}

	RemoveAndDelete();

	CreateEffect();

	for (auto obj : m_gameObjects)
	{
		obj->Update(delta_time);
	}

	m_sequence.update(delta_time);
}

void ScenePlay::Draw(float delta_time)
{
	m_backGround->Draw(delta_time, m_camera);
	
	if (m_stage_name == "stage1")
	{
		m_balloonInstruction->Draw(delta_time, m_camera);
	}
	
	if (m_stage_name == "stageBoss")
	{
		m_ui->SetIsDraw(true);
	}

	m_map->Draw(m_camera);

	for (auto obj : m_gameObjects) 
	{
		obj->Draw(delta_time, m_camera);
	}
}

void ScenePlay::Finalize()
{
	for (auto obj : m_gameObjects)
	{
		delete obj;
	}

	m_backGround->Finalize();

	m_map->Finalize();

	m_enemies.clear();
}

void ScenePlay::CreateEffect()
{
	if (m_player->GetIsDraw())
	{
		if 
		(
			!m_effectPlayer_beam->GetIsActive() 
			&&(tnl::Input::IsKeyDownTrigger(eKeys::KB_C)
				|| tnl::Input::IsPadDownTrigger(ePad::KEY_1))
		)
		{
			m_is_effect = true;

			MusicManager::GetInstance().PlaySE("beam");

			m_effectPlayer_beam->SetIsActive(true);

			m_effectPlayer_beam->SetPos(m_player->GetPos());

			m_effectPlayer_beam->SetOffset(tnl::Vector3(400, 0, 0));

			m_effectPlayer_beam->CalculateCollisionCircles();
		}
		else if 
		(
			!m_effectPlayer_fire->GetIsActive() 
			&&(tnl::Input::IsKeyDownTrigger(eKeys::KB_X) 
				|| tnl::Input::IsPadDownTrigger(ePad::KEY_0))
		)
		{
			m_is_effect = true;

			MusicManager::GetInstance().PlaySE("fire");

			m_effectPlayer_fire->SetIsActive(true);

			m_effectPlayer_fire->SetPos(m_player->GetPos());

			m_effectPlayer_fire->SetOffset(tnl::Vector3(270, 0, 0));

			m_effectPlayer_fire->CalculateCollisionCircles();
		}
	}
}

void ScenePlay::CreateEnemy(float delta_time)
{
	auto it = m_enemies_respawn_list.begin();

	while (it != m_enemies_respawn_list.end())
	{
		Enemy* enemy = it->first;

		float& respawn_timer = it->second;

		respawn_timer += delta_time;

		if (respawn_timer > 3.0f)
		{
			if (m_enemy_respawn_count < ENEMY_TOTAL_RESPAWNS)
			{
				const sEnemyPosData& respawn_data = enemy->GetEnemyData();

				m_enemy = new EnemyFairy
							(
								respawn_data
								, m_enemy_infos[respawn_data.s_type_id]
								, m_player
								, m_map
								, m_collision
								, m_camera
							);

				static_cast<EnemyFairy*>(m_enemy)->RandomType();

				m_enemies.emplace_back(m_enemy);

				m_gameObjects.emplace_back(m_enemy);
				// �Đ����񐔂𑝂₷
				m_enemy_respawn_count++;  
			}

			delete enemy;

			it = m_enemies_respawn_list.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool ScenePlay::SeqIdle(float delta_time)
{
	if (m_sequence.isStart())
	{
		InitMusic();
	}

	if (m_balloonClear->GetIsChangeGraphic())
	{
		m_player->SetIsDraw(false);

		m_is_change_scene = true;

		m_logo->SetIsClear(true);

		MusicManager::GetInstance().PlaySE("clear");

		m_logo->SetLogoState(eLogoType::Clear);
	}
	
	if
	(
		(m_is_change_scene 
			&& (tnl::Input::IsKeyDown(eKeys::KB_RETURN) 
				|| tnl::Input::IsPadDown(ePad::KEY_12)))
		||
		(m_player->GetIsDead() 
			&& (tnl::Input::IsKeyDown(eKeys::KB_RETURN)
				|| tnl::Input::IsPadDown(ePad::KEY_12)))
	)
	
	{
		MusicManager::GetInstance().StopBGM();
		
		MusicManager::GetInstance().PlaySE("enter");

		auto scene = SceneManager::GetInstance();

		scene->ChangeScene(new SceneTitle());
	}
	return true;
}

void ScenePlay::CollisionCheckBoss()
{
	if (!m_enemy->GetIsActiveBoss())
	{
		return;
	}

	// �{�X�̃G�t�F�N�g�̊e�����蔻��̈ʒu���擾
	std::vector<tnl::Vector3> collision_circles_boss 
		= m_effectBoss->GetCollisionCirclesPos();

	// �e�����蔻��ɑ΂��āA�v���C���[�Ƃ̏Փ˂��`�F�b�N
	for (auto circle_pos_boss : collision_circles_boss)
	{
		if 
		(
			wta::IsIntersectCircleCircle
			(circle_pos_boss
			, m_effectBoss->GetSize()
			, m_player->GetPos()
			, m_player->GetSize())
		)
		{
			// ���G��ԂłȂ��ꍇ�Ƀv���C���[��HP������
			if (!m_player->GetIsInvincible())
			{
				MusicManager::GetInstance().PlaySE("damaged");
				// HP������������
				m_player->DecreaseHP(1); 
				// ��莞�Ԗ��G��Ԃɂ���
				m_player->MakeInvincible(); 
				// ��ł������肪����΃��[�v�𔲂���
				break; 
			}
		}
	}
}

void ScenePlay::CollisionCheck(float delta_time)
{
	if (m_stage_name == "stageBoss")
	{
		CollisionCheckBoss();

		m_collision->CollisionCharacter(m_player, m_enemy);
	}

	for (auto enemy : m_enemies)
	{
		if (enemy->GetIsDead())
		{	
			// ���Ɏ���ł���G�ɑ΂��锻��̓X�L�b�v
			m_enemies_remove_list.emplace_back(enemy); 	
			
			if (m_stage_name == "stage3" && enemy->GetTypeID() == 3)
			{
				m_enemies_respawn_list.emplace_back(enemy,0.0f);
			}

			continue;
		}

		m_collision->CollisionCalculate(enemy, m_map, 10);

		m_collision->CollisionCharacter(m_player, enemy);
		
		for (auto effect : { m_effectPlayer_beam, m_effectPlayer_fire })
		{
			if (!effect->GetIsActive()) continue;

			bool effect_hit_enemy = false;

			for (auto circlePos : effect->GetCollisionCirclesPos())
			{
				if
				(
					wta::IsIntersectCircleCircle
					(circlePos, effect->GetSize()
					, enemy->GetPos()
					, enemy->GetSize())
				)
				{
					effect_hit_enemy = true;
					
					break;
				}
			}

			// 1�ȏ�̉~���G�Ƀq�b�g�����ꍇ�̏���
			if (effect_hit_enemy)
			{
				// ���G��ԂłȂ��ꍇ�ɓG��HP������
				if (!enemy->GetIsInvincible())
				{
					enemy->DecreaseHP(1); 

					enemy->MakeInvincible(); 
				}

				if (enemy->GetHp() <= 0)
				{
					MusicManager::GetInstance().PlaySE("dead");
					// HP��0�ȉ��̏ꍇ�A�G�����S�Ƃ���
					enemy->SetIsDead(true); 
				}

				break; 
			}
		}
	}
}

void ScenePlay::RemoveAndDelete()
{
	for (auto enemy : m_enemies_remove_list)
	{
		m_gameObjects.remove(enemy);

		m_enemies.remove(enemy);
	}

	m_enemies_remove_list.clear();
}