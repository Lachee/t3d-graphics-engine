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

	CameraOrbit::CameraOrbit(void)
	{
		
		xSpeed = 0.5;
		ySpeed = 0.5;
		scrollSpeed = 0.5;

		yMinLimit = -20;
		yMaxLimit = 80;

		distanceMin = 0.1;
		distanceMax = 50;
		distance = distanceMin + ((distanceMax - distanceMin) / 2);

		x = 0;
		y = 0;
	}


	CameraOrbit::~CameraOrbit(void)
	{
	}

	void CameraOrbit::update(float dt) {

		if (targetObject != NULL)
			targetPosition = targetObject->getTransform()->getWorldPosition();

		//Check if we have reset our things
		if (Input::keyDown[KEY_C])
		{
			setTarget(Vector3(0, 0, 0));
			distance = distanceMin + ((distanceMax - distanceMin) / 2);
			x = 0;
			y = 0;
		}

		//Update the distance
		if (Input::mouseDown[MOUSE_SCROLL_DOWN])
			distance += scrollSpeed;

		if (Input::mouseDown[MOUSE_SCROLL_UP])
			distance -= scrollSpeed;
		
		//clamp the distance and the y
		distance = Math::clamp(distance, distanceMin, distanceMax);		
		


		if (Input::mouseDown[MOUSE_LEFT])
		{
			//Move the positions around if we can
			x += Input::mouseX * -xSpeed * 0.02;
			y -= Input::mouseY * ySpeed * 0.02;
		
			y = Math::clamp(y, yMinLimit, yMaxLimit);
		}

		//Prepare our new rotation and set it
		Quaternion rotation = Quaternion(Vector3(y, x, 0));
		gameObject->getTransform()->setLocalRotation(rotation);

		if (Input::mouseDown[MOUSE_RIGHT])
		{
			//?We are gonna update our target position first
			Vector3 left = rotation.rotate(Vector3(1, 0, 0)) * Input::mouseX * -xSpeed *0.05;
			Vector3 up = rotation.rotate(Vector3(0, 1, 0)) * Input::mouseY * ySpeed *0.05;
			Vector3 pos = getTarget() + left + up;
			setTarget(pos);
		}

		//Prepare our new position and set it
		Vector3 negDistance = Vector3(0, 0, distance);
		Vector3 position = rotation.rotate(negDistance) + getTarget();
		gameObject->getTransform()->setLocalPosition(position);		
	}
	
	//Method to resolve the action of mouse movements
	void CameraOrbit::updateOrbit() 
	{

	}

}
