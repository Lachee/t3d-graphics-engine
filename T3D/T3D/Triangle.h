// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// Triangle.h
//
// Simple Triangle mesh with coloured sides

#ifndef Triangle_H
#define Triangle_H

#include "mesh.h"

namespace T3D
{
	class Triangle :
		public Mesh
	{
	public:
		Triangle(float width, float height, float thickness);
		virtual ~Triangle(void);
	};
}

#endif

