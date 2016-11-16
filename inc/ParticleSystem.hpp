/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:44:18 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/16 17:30:03 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

class	ParticleSystem {

	private:
		SDL		sdl;
		OpenGL	opengl;
		OpenCL	opencl;
		Shader	shader;
		Camera	camera;

		std::string	shape;
		glm::vec3	gravity_point;
		glm::vec3	backgroundColor;

		cl_uint		emitted;
		glm::vec3	emitter;

		std::vector<glm::vec3>	*emitters;

		float		step;

		void	setEmitter(glm::vec3 position);

	public:
		ParticleSystem();

		void	init(std::string shape);
		void	launch();
		void	update(bool anim, bool click);

		void	emit();

		void	randomColorSet();
		void	swapBackground();
		void	screenToWorld(unsigned int x, unsigned int y);

		void	printUsage() const;

		static std::string	readFile(std::string path);

		~ParticleSystem();

};

#endif
