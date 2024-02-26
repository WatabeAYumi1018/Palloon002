#include "wta_IsIntersectCalc.h"
#include <fstream>
#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"

namespace wta
{
	bool IsIntersectCircleCircle
	(
		const tnl::Vector3& pos1
		, float radius1
		, const tnl::Vector3& pos2
		, float radius2
	)
	{
		// 2�̈ʒu�x�N�g���̍��̒������v�Z
		float distance = (pos1 - pos2).length();

		// 2�̉~�̔��a�̘a�Ƃ̔�r
		return distance < (radius1 + radius2);
	}
}