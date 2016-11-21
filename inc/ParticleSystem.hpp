/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:44:18 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/21 11:37:34 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

class	ParticleSystem {

	private:
		SDL						sdl;
		OpenGL					opengl;
		OpenCL					opencl;
		Shader					shader;
		Camera					camera;

		float					step;
		float					speed;
		bool					paused;
		bool					click;
		std::string				shape;
		glm::vec3				gravity_point;
		glm::vec3				backgroundColor;

		cl_uint					emitted;
		std::vector<glm::vec3>	*emitters;

		void	setEmitter(glm::vec3 position);

	public:
		ParticleSystem();

		void	init(std::string shape);
		void	launch();
		void	update();
		void	emit();
		void	randomColorSet();
		void	swapBackground();
		void	screenToWorld(unsigned int x, unsigned int y);
		void	printUsage() const;

		static std::string	readFile(std::string path);

		~ParticleSystem();

};

#endif
