/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 16:00:56 by lfourque          #+#    #+#             */
/*   Updated: 2016/10/25 13:07:54 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "particle_system.h"

class	Camera {
	private:
		glm::mat4	_view;
		glm::mat4	_projection;

		Camera(Camera const & rhs);
		Camera &	operator=(Camera const & rhs);

	public:
		Camera();
		Camera(glm::mat4 view, glm::mat4 projection);

		void		setProjection(glm::mat4 projection);
		void		setView(glm::mat4 view);
		void		setPosition(float x, float y, float z);

		glm::mat4 &	projection();
		glm::mat4 &	view();

		~Camera();
};

#endif

