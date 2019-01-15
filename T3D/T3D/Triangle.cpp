
#include "Triangle.h"
#include "Math.h"
#include "Quaternion.h"
namespace T3D
{
	Triangle::Triangle(float width, float height, float thickness)
	{
		initArrays(24, 4, 6);

		float half_width = width / 2.0f;
		float half_thickness = thickness / 2.0f;

		//Calculate the angle
		float theta = std::atan((height / half_width));
		float eh = thickness / std::cos(theta);

		//Perform the maths and calculate the points
		Vector3 C = Vector3(0, height, 0);
		Vector3 E = Vector3(C.x, C.y + eh, 0);
		Vector3 A = Vector3(C.x -half_width, 0, 0);
	
		//Calculate directions
		Vector3 D1 = C - A; D1.normalise();
		Vector3 D2 = Quaternion::fromAngleAxis(Math::HALF_PI, Vector3(0, 0, 1)).rotate(D1);

		//Caclulate last 2 points
		Vector3 B = (D2 * thickness) + A;
		Vector3 D = (D2 * thickness) + C;

		//Add points
		int point = 0;
		setVertex(point++, A.x, A.y, half_thickness);	//0
		setVertex(point++, B.x, B.y, half_thickness);	//1
		setVertex(point++, C.x, C.y, half_thickness);	//2
		setVertex(point++, D.x, D.y, half_thickness);	//3
		setVertex(point++, E.x, E.y, half_thickness);	//4
		setVertex(point++, -A.x, A.y, half_thickness);	//5
		setVertex(point++, -B.x, B.y, half_thickness);	//6
		setVertex(point++, -D.x, D.y, half_thickness);	//7

		setVertex(point++, A.x, A.y, -half_thickness);	//0
		setVertex(point++, B.x, B.y, -half_thickness);	//1
		setVertex(point++, C.x, C.y, -half_thickness);	//2
		setVertex(point++, D.x, D.y, -half_thickness);	//3
		setVertex(point++, E.x, E.y, -half_thickness);	//4
		setVertex(point++, -A.x, A.y, -half_thickness);	//5
		setVertex(point++, -B.x, B.y, -half_thickness);	//6
		setVertex(point++, -D.x, D.y, -half_thickness);	//7

		//FRONT
		setFace(0, 0, 2, 3, 1);
		setFace(0, 2, 4, 3);
		setFace(1, 6, 7, 2, 5);
		setFace(1, 7, 4, 2);		
		
		//BACK
		setFace(2, 8 + 1, 8 + 3, 8 + 2, 8 + 0);
		setFace(2, 8 + 3, 8 + 4, 8 + 2);
		setFace(3, 8 + 5, 8 + 2, 8 + 7, 8 + 6);
		setFace(3, 8 + 2, 8 + 4, 8 + 7);

		//SIDES
		setVertex(point++, B.x, B.y, half_thickness);	//16 + 0 [16
		setVertex(point++, B.x, B.y, -half_thickness);	//16 + 1 [17
		setVertex(point++, E.x, E.y, half_thickness);	//16 + 2 [18
		setVertex(point++, E.x, E.y, -half_thickness);	//16 + 3 [19
		setFace(4, 18, 19, 17, 16);

		setVertex(point++, -B.x, B.y, half_thickness);		//20 + 0 [20
		setVertex(point++, -B.x, B.y, -half_thickness);	//20 + 1 [21
		setVertex(point++, E.x, E.y, half_thickness);		//20 + 2 [22
		setVertex(point++, E.x, E.y, -half_thickness);		//20 + 3 [23
		setFace(5, 20, 21, 23, 22);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();
	}


	Triangle::~Triangle(void)
	{
		// Mesh delete arrays if they have been created, not need to do anything here
	}
}
