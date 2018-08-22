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

		void updateOrbit();
		
		float distance = 100;

	private:

		Vector3 targetPosition;
		GameObject* targetObject = NULL;

		float keySensitivity;
		
		float yMinLimit, yMaxLimit;
		float xSpeed, ySpeed;
		float x, y;
	};

}

#endif

