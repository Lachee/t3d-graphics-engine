// =========================================================================================
// KIT307 - Computer Graphics and Games, 2018
// =========================================================================================
//
// Author: Lachlan Hopkins
//
// Pyramid.h
//
// Simple Pyramid mesh with coloured sides

#include "Pyramid.h"

namespace T3D
{
	Pyramid::Pyramid(float size)
	{
		// Init vertex and index arrays
		initArrays(4 + (4 * 3),				//1 quad (4) + 4 triangles (3) = 4 + (4 * 3) = 4 * 4
			4,		// num tris
			1);		// num quads


		//Index count of the vertex
		int pos = 0;
		float half_size = size / 2.0;
		
		//Add the bottom quad
		//
		setVertex(pos++, -half_size, 0, -half_size);
		setVertex(pos++, -half_size, 0, half_size);
		setVertex(pos++, half_size, 0, half_size);
		setVertex(pos++, half_size, 0, -half_size);

		//Front triangle
		setVertex(pos++, 0, size, 0);
		setVertex(pos++, -half_size, 0, half_size);
		setVertex(pos++, half_size, 0, half_size);

		//Back Traingle 
		setVertex(pos++, 0, size, 0);
		setVertex(pos++, -half_size, 0, -half_size);
		setVertex(pos++, half_size, 0, -half_size);
		
		setFace(0, 0, 1, 2, 3);
		setFace(0, 4, 5, 6);
		setFace(1, 7, 8, 9);


		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();

	}


	Pyramid::~Pyramid(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
