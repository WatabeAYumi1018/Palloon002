#include "Camera.h"
#include "../Character/Player/Player.h"
#include "../Map/Map.h"

void Camera::Update(float delta_time, Player* player, Map* map)
{
	Scroll(player, map);

	MoveRange(player, map);
}

//★背景とチップのスクロール値調節すること
void Camera::Scroll(Player* player, Map* map)
{
	//プレイヤーが画面中央に来たらスクロール開始
	if (!m_is_scroll)
	{
		if
			(
				player->GetPos().x > DXE_WINDOW_WIDTH >> 1
				|| player->GetPos().y > DXE_WINDOW_HEIGHT >> 1
				)
		{
			m_target = player->GetPos();

			m_is_scroll = true;
		}
	}
	else
	{
		//プレイヤーの座標を取得して、カメラの座標を遅延更新
		m_target += (player->GetPos() - m_target) * 0.1f;

		//プレイヤーが画面中央から外れたらスクロール終了
		if
			(
				(player->GetPos().x <= DXE_WINDOW_WIDTH >> 1
					&& player->GetPos().y <= DXE_WINDOW_HEIGHT >> 1)
				)
		{
			m_is_scroll = false;
		}
	}
}

//プレイヤーの座標を取得して、カメラの座標を更新する
void Camera::MoveRange(Player* player, Map* map)
{
	//スクロール開始座標
	const float halfWidth = DXE_WINDOW_WIDTH >> 1;

	const float halfHeight = DXE_WINDOW_HEIGHT >> 1;
	
	//カメラの移動範囲
	const float maxX = map->MAP_CHIP_SIZE * map->GetMapChipX() - halfWidth;

	const float maxY = map->MAP_CHIP_SIZE * map->GetMapChipY() - halfHeight;

	//横長、縦長、どちらにも対応可能にする
	if (halfWidth < maxX)
	{
		//clamp関数で範囲内に移動を収める。clamp(値, 最小値, 最大値)
		m_target.x = std::clamp(m_target.x, halfWidth, maxX);
	}
	else
	{
		//csvファイルのサイズがmaxとなる
		m_target.x = maxX;
	}

	m_target.y = std::clamp(m_target.y, halfHeight, maxY);
}
