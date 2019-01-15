#ifndef POLYGONMESH_H
#define POLYGONMESH_H

#include "clipper.hpp"
#include "earcut.hpp"
#include "Mesh.h"

using namespace ClipperLib;

namespace mapbox {
	namespace util {

		template <>
		struct nth<0, ClipperLib::IntPoint> {
			inline static auto get(const ClipperLib::IntPoint &t) {
				return t.X;
			};
		};
		template <>
		struct nth<1, ClipperLib::IntPoint> {
			inline static auto get(const ClipperLib::IntPoint &t) {
				return t.Y;
			};
		};

	} // namespace util
} // namespace mapbox

namespace T3D
{

	class Polygon :
		public Mesh
	{
	public:
		Polygon(Paths shape, float scale = 0.1f) {
			_shape = shape;
			_scale = scale;
			RecalculateMesh();
		}
		~Polygon() {}

		void SetScale(float scale) { _scale = scale; RecalculateMesh(); }
		void SetShape(Paths shape) { _shape = shape; RecalculateMesh(); }

		void Union(Paths shape, bool recalculate = true);
		void Intersect(Paths shape, bool recalculate = true);

	private:
		Paths _shape;
		float _scale;

		void RecalculateMesh();
	};


}
#endif