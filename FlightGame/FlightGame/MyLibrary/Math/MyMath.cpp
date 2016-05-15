#define _USE_MATH_DEFINES
#include<math.h>
#include"MyMath.h"

namespace oka
{
	float MyMath::ToRadian(const float _degree)
	{
		return _degree*((float)M_PI / 180.0f);
	}
}