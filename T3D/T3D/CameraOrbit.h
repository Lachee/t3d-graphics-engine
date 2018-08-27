// =========================================================================================
// KIT307 Computer Graphics and Games
// =========================================================================================
//
// Author: Lachlan Hopkins
//
// cameraorbit.h
//
// Component to add a orbit camera

#ifndef CAMERAORBIT_H
#define CAMERAORBIT_H

#include "component.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "GameObject.h"
#include "Transform.h"

namespace T3D
{

	class CameraOrbit :
		public Component
	{
	public:
		CameraOrbit(void);
		virtual ~CameraOrbit(void);
		virtual void update(float dt);

		void setTarget(GameObject* target) { targetObject = target; }
		void setTarget(Vector3 position) { targetPosition = position; targetObject = NULL; }
		Vector3 getTarget() { return targetObject == NULL ? targetPosition : targetObject->getTransform()->getWorldPosition(); }

		void updateOrbit();

		float xSpeed, ySpeed, scrollSpeed;

		float yMinLimit, yMaxLimit;
		float distanceMin, distanceMax;

	private:

		Vector3 targetPosition;
		GameObject* targetObject = NULL;
				
		float x, y; 
		float distance = 100;

	};

}

#endif

