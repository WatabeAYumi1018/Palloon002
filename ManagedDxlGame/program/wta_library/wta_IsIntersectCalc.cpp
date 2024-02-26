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
		// 2‚Â‚ÌˆÊ’uƒxƒNƒgƒ‹‚Ì·‚Ì’·‚³‚ğŒvZ
		float distance = (pos1 - pos2).length();

		// 2‚Â‚Ì‰~‚Ì”¼Œa‚Ì˜a‚Æ‚Ì”äŠr
		return distance < (radius1 + radius2);
	}
}