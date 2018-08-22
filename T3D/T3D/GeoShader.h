// =========================================================================================
// KIT307 Computer Graphics and Games
// =========================================================================================
//
// Author: Lachlan Hopkins
//
// GeoShader.h
//
// Class for creating and compiling a GLSL shader

#pragma once

#include "shader.h"

namespace T3D {

	class GeoShader : public Shader
	{
	public:
		GeoShader(std::string vertFilename, std::string geoFilename, std::string fragFilename);
		~GeoShader(void);

		virtual void compileShader();
		virtual void bindShader();
		virtual void unbindShader();
	protected:
		std::string geoSource;

		unsigned int vertID;
		unsigned int fragID;
		unsigned int geoID;
		unsigned int id;
	};

}

