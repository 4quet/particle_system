/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:44:18 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/10 18:56:54 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

# include "particle_system.h"

class	ParticleSystem {

	private:
		SDL		sdl;
		OpenGL	opengl;
		OpenCL	opencl;
		Shader	shader;
		Camera	camera;

		std::string	shape;
		glm::vec4	gravity_point;
		glm::vec4	backgroundColor;

	public:
		ParticleSystem();

		void	init(std::string shape);
		void	launch();
		void	update(bool anim, bool click);

		void	randomColorSet();
		void	swapBackground();
		void	screenToWorld(unsigned int x, unsigned int y);

		static std::string	readFile(std::string path);

		~ParticleSystem();

};

#endif
