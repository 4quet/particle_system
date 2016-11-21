/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:52:13 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/21 11:25:03 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle_system.hpp"

OpenGL::OpenGL() {
	initVBOs();
	initVAO();
}

void	OpenGL::initVBOs() {
	GLuint	size;

	size = sizeof(cl_float3) * static_cast<GLuint>(MAX_EMITTED_AMOUNT + g_ParticlesAmount);

	glGenBuffers(1, &pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);

	glGenBuffers(1, &vel_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vel_vbo);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);
}

void	OpenGL::initVAO() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cl_float3), NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void	OpenGL::render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, MAX_EMITTED_AMOUNT + g_ParticlesAmount);
	glBindVertexArray(0);
}

float	OpenGL::getXCoord(unsigned int x) {
	return 2.0f * (x / (float)WIN_WIDTH) - 1.0f;
}

float	OpenGL::getYCoord(unsigned int y) {
	return 1.0f - (2.0f * (y / (float)WIN_HEIGHT));
}

OpenGL::~OpenGL() {

}
