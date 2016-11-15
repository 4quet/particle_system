/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OpenGL.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:52:13 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/15 14:48:15 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle_system.h"

OpenGL::OpenGL() {
	initVBOs();
	initVAO();
}

void	OpenGL::initVBOs() {
	GLuint	size;

	size = sizeof(cl_float3) * static_cast<GLuint>(PARTICLES_AMOUNT + MAX_EMITTED_AMOUNT);

	glGenBuffers(1, &pos_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);

	glGenBuffers(1, &vel_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vel_vbo);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW);

	//
}

void	OpenGL::initVAO() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, pos_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cl_float3), NULL);
	glEnableVertexAttribArray(0);

//	glBindBuffer(GL_ARRAY_BUFFER, vel_vbo);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(cl_float3), NULL);
//	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void	OpenGL::render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, PARTICLES_AMOUNT + MAX_EMITTED_AMOUNT);
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
