#pragma once
#include <vector>
#include "../library/tnl_math.h"

/////////////////////////////////////////////////////////////////////////////////////////
// 
// 当たり判定の計算を行う関数群（必要に応じて追加）
//
/////////////////////////////////////////////////////////////////////////////////////////

namespace wta
{
	// 円同士の当たり判定計算
    // arg1... 円１の中心座標
    // arg2... 円１の半径
    // arg3... 円２の中心座標
    // arg4... 円２の半径
    // return... 重なっているかどうか(true:重なっている false:重なっていない)
    // tips ... 円の当たり判定は、円の中心座標間の距離が、円の半径の和よりも小さいかどうかで判定できます
    bool IsIntersectCircleCircle(const tnl::Vector3& pos1, float radius1, const tnl::Vector3& pos2, float radius2);
}