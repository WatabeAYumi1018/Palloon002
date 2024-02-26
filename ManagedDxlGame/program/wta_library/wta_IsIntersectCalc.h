#pragma once
#include <vector>
#include "../library/tnl_math.h"

/////////////////////////////////////////////////////////////////////////////////////////
// 
// �����蔻��̌v�Z���s���֐��Q�i�K�v�ɉ����Ēǉ��j
//
/////////////////////////////////////////////////////////////////////////////////////////

namespace wta
{
	// �~���m�̓����蔻��v�Z
    // arg1... �~�P�̒��S���W
    // arg2... �~�P�̔��a
    // arg3... �~�Q�̒��S���W
    // arg4... �~�Q�̔��a
    // return... �d�Ȃ��Ă��邩�ǂ���(true:�d�Ȃ��Ă��� false:�d�Ȃ��Ă��Ȃ�)
    // tips ... �~�̓����蔻��́A�~�̒��S���W�Ԃ̋������A�~�̔��a�̘a�������������ǂ����Ŕ���ł��܂�
    bool IsIntersectCircleCircle(const tnl::Vector3& pos1, float radius1, const tnl::Vector3& pos2, float radius2);
}