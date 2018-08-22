// KIT307 Computer Graphics and Games
// =========================================================================================
//
// Author: Lachlan Hopkins
//
// GeoShader.cpp
//
// Class for creating and compiling a GLSL shader


#include "GeoShader.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <iostream>
#include <fstream>

namespace T3D {

	GeoShader::GeoShader(std::string vertFilename, std::string geoFilename, std::string fragFilename) : Shader(vertFilename, fragFilename)
	{
		std::ifstream geofile(geoFilename);

		geoSource = "";
		while (geofile.good()) {
			std::string line;
			std::getline(geofile, line);
			geoSource.append(line + "\n");
		}
	}


	GeoShader::~GeoShader(void)
	{
	}

	void GeoShader::compileShader() {
		//std::cout << "Compiling shader...\n";
		//std::cout << vertSource << "\n\n";
		//std::cout << fragSource << "\n\n";

		vertID = glCreateShader(GL_VERTEX_SHADER);
		geoID = glCreateShader(GL_GEOMETRY_SHADER);
		fragID = glCreateShader(GL_FRAGMENT_SHADER);

		GLchar const *vert = vertSource.c_str();
		GLint const vertLength = vertSource.size();
		GLchar const *frag = fragSource.c_str();
		GLint const fragLength = fragSource.size();
		GLchar const *geo = geoSource.c_str();
		GLint const geoLength = geoSource.size();

		GLint result;

		glShaderSource(vertID, 1, &vert, &vertLength);
		glShaderSource(geoID, 1, &geo, &geoLength);
		glShaderSource(fragID, 1, &frag, &fragLength);


		glCompileShader(vertID);
		glGetShaderiv(vertID, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE) {
			std::cout << "Vertex program " << vertID << " did not compile...\n";
			GLchar* log;
			GLint length;
			glGetShaderiv(vertID, GL_INFO_LOG_LENGTH, &length);
			log = (GLchar*)malloc(length);
			glGetShaderInfoLog(vertID, length, &length, log);
			std::cout << log << "\n";
		}
		else {
			std::cout << "Vertex program "<< vertID << " compiled successfully\n";
		}

		glCompileShader(geoID);
		glGetShaderiv(geoID, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE) {
			std::cout << "Geo program " << geoID << " did not compile...\n";
			GLchar* log;
			GLint length;
			glGetShaderiv(geoID, GL_INFO_LOG_LENGTH, &length);
			log = (GLchar*)malloc(length);
			glGetShaderInfoLog(geoID, length, &length, log);
			std::cout << log << "\n";
		}
		else {
			std::cout << "Geo program " << geoID << " compiled successfully\n";
		}

		glCompileShader(fragID);
		glGetShaderiv(fragID, GL_COMPILE_STATUS, &result);
		if (result != GL_TRUE) {
			std::cout << "Fragment program " << fragID << " did not compile...\n";
		}
		else {
			std::cout << "Fragment program "<< fragID << " compiled successfully\n";
		}


		//Check for compile errors (TODO)

		id = glCreateProgram();

		glAttachShader(id, vertID);
		glAttachShader(id, geoID);
		glAttachShader(id, fragID);

		glLinkProgram(id);
		glGetShaderiv(id, GL_LINK_STATUS, &result);
		if (result != GL_TRUE) {
			std::cout << "Error linking shader...\n";
		}
		else {
			//std::cout << "Shader program "<< id << " linked successfully\n";
		}

		//Check for link errors (TODO)
	}

	void GeoShader::bindShader() {
		glUseProgram(id);
	}

	void GeoShader::unbindShader() {
		glUseProgram(0);
	}

}
