/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 16:00:28 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/04 16:57:58 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle_system.h"

Camera::Camera() {
	_projection = glm::perspective(45.0f, (float)WIN_WIDTH / (float)WIN_HEIGHT, 1.0f, 100.0f);
	_view = glm::lookAt( glm::vec3(0.0f, 0.0f, -5.0f),
						 glm::vec3(0.0f, 0.0f,  0.0f),
						 glm::vec3(0.0f, 1.0f,  0.0f) );
}

Camera::Camera(glm::mat4 view, glm::mat4 projection) : 
	_view(view), _projection(projection) { }

glm::mat4 &	Camera::projection() { return (_projection); }
glm::mat4 &	Camera::view() { return (_view); }

void		Camera::setView(glm::mat4 view) { _view = view; }
void		Camera::setProjection(glm::mat4 projection) { _projection = projection; }

void		Camera::setPosition(float x, float y, float z) {
	_view = glm::lookAt( glm::vec3(x, y, z),
						 glm::vec3(0.0f, 0.0f,  0.0f),
						 glm::vec3(0.0f, 1.0f,  0.0f) );
}

Camera::~Camera() {

}

