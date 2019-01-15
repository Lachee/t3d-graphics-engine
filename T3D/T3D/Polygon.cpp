#include "Polygon.h"

namespace T3D
{
	void Polygon::Union(Paths shape, bool recalculate)
	{
		//Prepare clipper and solution
		Paths solution;
		Clipper c;

		//Do the union
		c.AddPaths(_shape, ptSubject, true);
		c.AddPaths(shape, ptClip, true);
		c.Execute(ctUnion, solution, pftNonZero, pftNonZero);

		//Update the shape to the result
		_shape = solution;

		//Recalculate if required.
		if (recalculate) RecalculateMesh();
	}

	void Polygon::Intersect(Paths shape, bool recalculate)
	{
		//Prepare clipper and solution
		Paths solution;
		Clipper c;

		//Do the union
		c.AddPaths(_shape, ptSubject, true);
		c.AddPaths(shape, ptClip, true);
		c.Execute(ctIntersection, solution, pftNonZero, pftNonZero);

		//Update the shape to the result
		_shape = solution;

		//Recalculate if required.
		if (recalculate) RecalculateMesh();
	}

	void Polygon::RecalculateMesh() 
	{
		using Coord = double;
		using N = uint32_t;
		std::vector<N> triangles = mapbox::earcut<N>(_shape);

		//Prepare the number of verts and triangles then calculate them
		int numVerts = 0;
		int numTris = 0;
		for (int i = 0; i < _shape.size(); i++) numVerts += _shape[i].size();
		numTris = triangles.size() / 3;

		//Set the mesh count and cleanup old mesh
		if (vertices) delete[]vertices;
		if (triIndices) delete[]triIndices;
		if (quadIndices) delete[]quadIndices;
		if (normals) delete[]normals;
		if (colors) delete[]colors;
		if (uvs) delete[]uvs;

		initArrays(numVerts, numTris, 0);

		//Add all the verticies
		int current_vertext = 0;
		for (int j = 0; j < _shape.size(); j++)
			for (int i = 0; i < _shape[j].size(); i++)
				setVertex(current_vertext++, _shape[j][i].X * _scale, _shape[j][i].Y * _scale, 0);
		
		//Add all the triangles
		int current_triangle = 0;
		for (int t = 0; t < triangles.size(); t += 3)
			setFace(current_triangle++, triangles[t + 0], triangles[t + 1], triangles[t + 2]);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();
	}
}


#if OLDSYSTEMDELETEINFUTURE

// The number type to use for tessellation
using Coord = double;

// The index type. Defaults to uint32_t, but you can also pass uint16_t if you know that your
// data won't have more than 65536 vertices.
using N = uint32_t;

Paths subj(2), clip(1), solution;

//define outer blue 'subject' polygon
subj[0] <<
IntPoint(180, 200) << IntPoint(260, 200) <<
IntPoint(260, 150) << IntPoint(180, 150);

//define subject's inner triangular 'hole' (with reverse orientation)
subj[1] <<
IntPoint(215, 160) << IntPoint(230, 190) << IntPoint(200, 190);
//
////define orange 'clipping' polygon
//clip[0] << IntPoint(100, 0) << IntPoint(100, 100) << IntPoint(0, 100) << IntPoint(0, 0);
//
////perform intersection ...
//Clipper c;
//c.AddPaths(subj, ptSubject, true);
//c.AddPaths(clip, ptClip, true);
//c.Execute(ctIntersection, solution, pftNonZero, pftNonZero);

// Run tessellation
// Returns array of indices that refer to the vertices of the input polygon.
// e.g: the index 6 would refer to {25, 75} in this example.
// Three subsequent indices form a triangle. Output triangles are clockwise.
std::vector<N> indices = mapbox::earcut<N>(subj);

int numVerts = subj[0].size() + subj[1].size();
int numTris = indices.size() / 3;
initArrays(numVerts, numTris, 0);

int curVert = 0;
int curTri = 0;

//Set every vert.
for (int j = 0; j < subj.size(); j++)
{
	for (int i = 0; i < subj[j].size(); i++)
	{
		setVertex(curVert++, subj[j][i].X * scale, subj[j][i].Y * scale, 0);
	}
}

//Set every triangle
for (int t = 0; t < indices.size(); t += 3)
{
	setFace(curTri++, indices[t + 0], indices[t + 1], indices[t + 2]);
}


// Check vertex and index arrays
checkArrays();

// Calculate normals
calcNormals();
#endif