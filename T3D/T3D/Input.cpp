// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// input.cpp
//
// Simple static class to track keyboard and mouse
// Adapted from Ogre3D

#include "Input.h"

namespace T3D
{
	bool Input::mouseDown[16];
	bool Input::keyDown[512];
	int Input::mouseX = 0;
	int Input::mouseY = 0;

	void Input::init(){
		for (int i = 0; i<512; i++) {
			keyDown[i] = false;
		}		
		
		for (int i = 0; i<5; i++) {
			mouseDown[i] = false;
		}
		mouseX = 0; mouseY = 0;
	}

	void Input::onMouseDown(int mousecode) 
	{
		mouseDown[mousecode] = true;
	}

	void Input::onMouseUp(int mousecode)
	{
		mouseDown[mousecode] = false;
	}

	void Input::onKeyDown(int keycode){
		keyDown[keycode] = true;
	}

	void Input::onKeyUp(int keycode){
		keyDown[keycode] = false;
	}

	void Input::onMouseMotion(int dx, int dy){
		mouseX = dx;
		mouseY = dy;
	}
}
