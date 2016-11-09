/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:43:01 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/09 15:30:55 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle_system.h"

ParticleSystem::ParticleSystem() {
	opencl.buffers.push_back(
			cl::BufferGL(opencl.context, CL_MEM_READ_WRITE, opengl.pos_vbo, NULL)
	);
	opencl.buffers.push_back(
			cl::BufferGL(opencl.context, CL_MEM_READ_WRITE, opengl.vel_vbo, NULL)
	);
	opencl.loadCLProgram("kernels/shape.cl");
}

void	ParticleSystem::init() {

	gravity_point = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	cl::Kernel	kernel(opencl.program, "sphere");

	kernel.setArg(0, opencl.buffers[0]);
	kernel.setArg(1, opencl.buffers[1]);
	kernel.setArg(2, PARTICLES_AMOUNT);

	opencl.queue.enqueueAcquireGLObjects(&opencl.buffers);
	opencl.queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(PARTICLES_AMOUNT),
			cl::NullRange);
	opencl.queue.finish();
	opencl.queue.enqueueReleaseGLObjects(&opencl.buffers);
	opencl.queue.finish();
}

void	ParticleSystem::launch() {
	SDL_Event		event;
	bool			quit = false;
	bool			click = false;
	bool			anim = false;

	glm::mat4	model;

	model = glm::mat4();

//	shader.addUniform("model");
	shader.addUniform("view");
	shader.addUniform("projection");

//	glEnable(GL_DEPTH_TEST);
//	glDepthMask(GL_TRUE);
//	glDepthFunc(GL_ALWAYS); // Change this to whatever kind of depth testing you want
//	glDepthRange(0.0f, 1.0f);
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch( event.type ) {
				case SDL_KEYDOWN:
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (anim == false)
						anim = true;
					if (event.button.button == SDL_BUTTON_LEFT)
						click = true;
					else if (event.button.button == SDL_BUTTON_RIGHT)
					{
						anim = false;
						init();
					}
					break;
				case SDL_MOUSEBUTTONUP:
					click = false;
					break;
				case SDL_MOUSEMOTION:
					if (click)
						screenToWorld(event.motion.x, event.motion.y);
					break;
				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		 glClear(GL_COLOR_BUFFER_BIT);

		 shader.use();

//		 shader.setUniformMatrix(model, "model");
		 shader.setUniformMatrix(camera.view(), "view");
		 shader.setUniformMatrix(camera.projection(), "projection");

		 if (anim)
			 update();

		 opengl.render();

		 shader.disable();

		 SDL_GL_SwapWindow(sdl.win);

	}
}

void	ParticleSystem::update() {
	/*
		*/
	static std::clock_t		oldTime = std::clock();
	std::clock_t			currentTime;
	cl_float				deltaTime;

		currentTime = std::clock();
		deltaTime = 1000.0f * (currentTime - oldTime) / CLOCKS_PER_SEC;
		oldTime = currentTime;

		cl_float	dt = 0.0000001;
		(void)dt;

		float	*gp = glm::value_ptr(gravity_point);
		(void)gp;

		cl::Kernel	kernel(opencl.program, "update");
		kernel.setArg(0, opencl.buffers[0]);
		kernel.setArg(1, opencl.buffers[1]);
		kernel.setArg(2, sizeof(cl_float4), gp);
		kernel.setArg(3, sizeof(cl_float), &deltaTime);

		glFinish();

		opencl.queue.enqueueAcquireGLObjects(&opencl.buffers);
		opencl.queue.enqueueNDRangeKernel(kernel, cl::NullRange,
				cl::NDRange(PARTICLES_AMOUNT),
				cl::NullRange);
		opencl.queue.finish();
		opencl.queue.enqueueReleaseGLObjects(&opencl.buffers);
}

void	ParticleSystem::screenToWorld(unsigned int x, unsigned int y) {

	float	glX = opengl.getXCoord(x);
	float	glY = opengl.getYCoord(y);

	glm::mat4	invP = glm::inverse(camera.projection() * camera.view());
	glm::vec4	screenPos = glm::vec4(glX, glY, 1.f, 1.f);
	glm::vec4	worldPos = invP * screenPos;


	gravity_point = glm::vec4(camera.position(), 1.f) + worldPos * 60.f;
}

std::string	ParticleSystem::readFile(std::string path) {
	std::stringstream	stream;
	std::ifstream		file(path.c_str());

	if (!file.good())
		throw std::runtime_error("Failed to open file :" + path);
	stream << file.rdbuf();
	file.close();
	return stream.str();
}

ParticleSystem::~ParticleSystem() {

}

