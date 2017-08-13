// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Lachlan Hopkins
//
// FileMesh.h
//
// Reads files that have been generated with T3D Exporter (for blender) and generates meshes for them.
//

#ifndef FILEMESH_H
#define FILEMESH_H

#include "mesh.h"

namespace T3D
{
	class FileMesh :
		public Mesh
	{
	public:
		FileMesh(char* file);
		virtual ~FileMesh(void);
	};
}

#endif

