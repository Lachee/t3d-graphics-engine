// =========================================================================================
// KIT307 Computer Graphics and Games
// =========================================================================================
//
// Author: Lachlan Hopkins
//
// cameraorbit.cpp
//
// Component to add a orbit camera

#include <iostream>

#include "CameraOrbit.h"

#include "Input.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Transform.h"
#include "Math.h"

namespace T3D
{
	//min and max speeds for key and mouse sensitivity
#define KEY_SENSITIVITY_MIN 50
#define KEY_SENSITIVITY_MAX 100
#define MOUSE_SENSITIVITY_MIN 0.0005f;
#define MOUSE_SENSITIVITY_MAX 0.0010f;

	CameraOrbit::CameraOrbit(void)
	{
		keySensitivity = 50.0f;
		
		xSpeed = 0.005;
		ySpeed = 0.5;

		yMinLimit = -20;
		yMaxLimit = 80;

		distance = -50;
		x = 0;
		y = 0;
	}


	CameraOrbit::~CameraOrbit(void)
	{
	}

	void CameraOrbit::update(float dt) {

		if (targetObject != NULL)
			targetPosition = targetObject->getTransform()->getWorldPosition();

		//resolve all of the input actions
		updateOrbit();

	}
	
	//Method to resolve the action of mouse movements
	void CameraOrbit::updateOrbit() 
	{
		x += Input::mouseX * xSpeed * distance * 0.02;
		y -= Input::mouseY * ySpeed * 0.02;

		y = Math::clamp(y, yMinLimit, yMaxLimit);

		Quaternion rotation = Quaternion(Vector3(y, x, 0));

		Vector3 negDistance = Vector3(0, 0, -distance);
		Vector3 position = rotation.rotate(negDistance) + targetPosition;
		
		gameObject->getTransform()->setLocalPosition(position);
		gameObject->getTransform()->setLocalRotation(rotation);
	}

}
