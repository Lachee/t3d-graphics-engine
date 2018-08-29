// =========================================================================================
// KIT307 - Computer Graphics and Games, 2018
// =========================================================================================
//
// Author: Lachlan Hopkins
//
// Pyramid.h
//
// Simple Pyramid mesh with coloured sides

#ifndef PYRAMID_H
#define PYRAMID_H

#include "mesh.h"

namespace T3D
{
	class Pyramid :
		public Mesh
	{
	public:
		Pyramid(float size);
		virtual ~Pyramid(void);
	};
}

#endif

