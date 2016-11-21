/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 16:00:28 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/21 10:51:51 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle_system.hpp"

Camera::Camera() {
	_position = glm::vec3(0.f, 0.f, -2.5f);
	_projection = glm::perspective( 45.0f,
									(float)WIN_WIDTH / (float)WIN_HEIGHT,
									Z_NEAR, Z_FAR);
	_view = glm::lookAt( _position,
						 glm::vec3(0.0f, 0.0f,  0.0f),
						 glm::vec3(0.0f, 1.0f,  0.0f) );
}

glm::vec3 &	Camera::position() { return (_position); }
glm::mat4 &	Camera::projection() { return (_projection); }
glm::mat4 &	Camera::view() { return (_view); }

void		Camera::setView(glm::mat4 view) { _view = view; }
void		Camera::setProjection(glm::mat4 projection) { _projection = projection; }

void		Camera::setPosition(float x, float y, float z) {
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_view = glm::lookAt( glm::vec3(x, y, z),
						 glm::vec3(x, y,  0.0f),
						 glm::vec3(0.0f, 1.0f,  0.0f) );
}

Camera::~Camera() {

}
