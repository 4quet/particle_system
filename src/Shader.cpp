/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/15 15:33:25 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/04 10:17:12 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle_system.h"

Shader::Shader() {
	std::string	vertexCode;
	std::string	fragmentCode;
	GLint		status;

	GLuint		vertexId;
	GLuint		fragmentId;
	
	vertexCode = ParticleSystem::readFile("shaders/SimpleShader.vert");
	fragmentCode = ParticleSystem::readFile("shaders/SimpleShader.frag");

	vertexId = compile(vertexCode, GL_VERTEX_SHADER);
	fragmentId = compile(fragmentCode, GL_FRAGMENT_SHADER);

	programId = glCreateProgram();
	glAttachShader(programId, vertexId);
	glAttachShader(programId, fragmentId);

	glLinkProgram(programId);
	
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
		throw std::runtime_error("Shader program link failed");
	else
		std::cout << "Shader program link OK\n";
}

GLuint		Shader::compile(std::string source, GLenum type) {
	GLuint			shaderID;
	const GLchar	*charSource;
	GLint			status;

	shaderID = glCreateShader(type);
	if (shaderID == 0)
		throw std::runtime_error("Could not create shader");
	charSource = source.c_str();

	glShaderSource(shaderID, 1, &charSource, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		throw std::runtime_error("Shader compilation failed");
	}
	else
		std::cout << "Compilation OK\n";
	return shaderID;
}

void		Shader::addUniform(std::string name) {
	_uniform[name] = glGetUniformLocation(programId, name.c_str());
	if (_uniform[name] == -1)
		throw std::runtime_error("Could not create uniform " + name);
}

GLint		Shader::uniform(std::string name) {
	static std::map<std::string, int>::const_iterator uniformIter;

	uniformIter = _uniform.find(name);
	if (uniformIter == _uniform.end())
		throw std::runtime_error("Could not find uniform in shader program: " + name);
	return _uniform[name];
}

void		Shader::setUniformMatrix (glm::mat4 mat, std::string name) {
	glUniformMatrix4fv(uniform(name), 1, GL_FALSE, glm::value_ptr(mat));
}

Shader::~Shader() {}

