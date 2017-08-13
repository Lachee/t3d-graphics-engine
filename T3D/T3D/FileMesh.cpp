// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Lachlan Hopkins
//
// FileMesh.cpp
//
// Reads files that have been generated with T3D Exporter (for blender) and generates meshes for them.
//

#include "FileMesh.h"
#include <stdio.h>
#include <stdlib.h>

namespace T3D
{
	FileMesh::FileMesh(char* file)
	{
		FILE *fid;
		fid = fopen(file, "r");

		int vertices;
		fscanf_s(fid, "vertices: %d\n", &vertices);

		int triangles;
		fscanf_s(fid, "triangles: %d\n", &triangles);

		initArrays(vertices, triangles, 0);

		//Read every vertices
		for (int i = 0; i < vertices; i++) {
			
			//Scan in the data
			int index;
			float x, y, z;
			fscanf_s(fid, "%d:%f,%f,%f\n", &index, &x, &y, &z);

			//Add it to the mesh
			setVertex(index, x, y, z);
		}

		//Read every triangle
		for (int i = 0; i < triangles; i++) {
			
			//Scan in the data
			int a, b, c;
			fscanf_s(fid, "%d,%d,%d\n", &a, &b, &c);

			//Set the triangle
			setFace(i, a, b, c);
		}

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();
	}


	FileMesh::~FileMesh(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
