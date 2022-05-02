#pragma once
#include "MADRengine/MADRpch.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Events.h"
#include "Components.h"
#include "IDControl.h"

class Component : public EventListener
{
private:
	IDController::MADR_ID ID;

public:
	IDController::MADR_ID GetID() { return ID; }

	void EventResponse(EVENT e)
	{

	}
};

class MADREntity : public EventListener 
{
	MADREntity* parent;
};


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

void DeleteComponent(Component*);

namespace Transform {

	class TransformComponent : public Component
	{
	private:
		glm::ivec3 worldPosition;
	public:
		glm::vec3 GetWorldPosition() { return FixedPointArith::ConvertFromIntVec(worldPosition); }
		//glm::vec3 GetLocalPosition() {return FixedPointArith::ConvertFromIntVec()};
	};
} //End of Transform Namespace