#pragma once
#include "MADRengine/MADRpch.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace FixedPointArith
{
	const unsigned int MAX_DECIMAL_PRECISION = 10000;
	const int INT360 = 3600000;
	glm::ivec3 ConvertFromFloatVec(const glm::vec3 floatVec)
	{
		return 	glm::ivec3((int)(floatVec.x * MAX_DECIMAL_PRECISION),
			(int)(floatVec.y * MAX_DECIMAL_PRECISION),
			(int)(floatVec.z * MAX_DECIMAL_PRECISION));
	}
	glm::vec3 ConvertFromIntVec(const glm::ivec3 intVec)
	{
		return glm::vec3((float)intVec.x / MAX_DECIMAL_PRECISION,
			(float)intVec.y / MAX_DECIMAL_PRECISION,
			(float)intVec.z / MAX_DECIMAL_PRECISION);
	}
} //End of FixedPointArith Namespace

class PhysicsTransform 
{
private:
	glm::ivec3 worldPosition;
public:
	glm::vec3 GetWorldPosition() { return FixedPointArith::ConvertFromIntVec(worldPosition); }
	glm::vec3 GetLocalPosition(glm::ivec3 relativeTo) 
	{
		glm::ivec3 temp;
		if (relativeTo.x > worldPosition.x)
			temp.x = relativeTo.x - worldPosition.x;
		else
			temp.x = worldPosition.x - relativeTo.x;

		if (relativeTo.y > worldPosition.y)
			temp.y = relativeTo.y - worldPosition.y;
		else
			temp.y = worldPosition.y - relativeTo.y;

		if (relativeTo.z > worldPosition.z)
			temp.z = relativeTo.z - worldPosition.z;
		else
			temp.z = worldPosition.z - relativeTo.z;

		return FixedPointArith::ConvertFromIntVec(temp); 
	}
};