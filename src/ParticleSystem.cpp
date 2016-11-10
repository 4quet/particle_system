/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:43:01 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/10 19:05:08 by lfourque         ###   ########.fr       */
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

void	ParticleSystem::init(std::string shape_to_init) {

	gravity_point = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
	shape = shape_to_init;
	cl::Kernel	kernel(opencl.program, shape.c_str());

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

	glm::vec3	newPos;
	float		step = -camera.position().z * 0.02;

	shader.addUniform("view");
	shader.addUniform("projection");
	shader.addUniform("gravity_point");
	shader.addUniform("camera_position");

//	shader.addUniform("border_color");
//	shader.addUniform("center_color");

	while (!quit)
	{
		const Uint8	*keyboardState = SDL_GetKeyboardState(NULL);

		shader.use();
		newPos = camera.position();

		if (keyboardState[SDL_SCANCODE_W] && newPos.z < 0)
			newPos.z += step;
		if (keyboardState[SDL_SCANCODE_S] && newPos.z > -(Z_FAR - 5))
			newPos.z -= step;
		if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT])
			newPos.x += step;
		if (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT])
			newPos.x -= step;

		if (keyboardState[SDL_SCANCODE_UP])
			newPos.y += step;
		if (keyboardState[SDL_SCANCODE_DOWN])
			newPos.y -= step;

		if (camera.position() != newPos)
		{
			camera.setPosition(newPos.x, newPos.y, newPos.z);
			glUniform3f(shader.uniform("camera_position"), newPos.x,
				newPos.y, newPos.z);
			step = -newPos.z * 0.02;
		}


		while (SDL_PollEvent(&event))
		{
			switch( event.type ) {
				case SDL_KEYDOWN:
					switch( event.key.keysym.sym ){
						case SDLK_ESCAPE:
							quit = true;
							break;
						case SDLK_SPACE:
							anim = !anim;
							break;
						case SDLK_TAB:
							shape = (shape == "sphere") ? "cube" : "sphere";
							anim = false;
							init(shape);
							break;
						case SDLK_RETURN:
							swapColorSet();
							break;
					}
					break;
				/*
				case SDL_KEYUP:
					switch( event.key.keysym.sym ){
						case SDLK_w:
							printf("UP newZ = 0\n");
							newZ = 0;
							break;
						case SDLK_s:
							newZ = 0;
							break;
					}
					*/
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						click = true;
						anim = true;
					}
					else if (event.button.button == SDL_BUTTON_RIGHT)
					{
						anim = false;
						init(shape);
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

		
		/*
		 glClearColor(	backgroundColor.x
				 		backgroundColor.y
				 		backgroundColor.z
				 		backgroundColor.w);
						*/
		 glClear(GL_COLOR_BUFFER_BIT);

		 shader.setUniformMatrix(camera.view(), "view");
		 shader.setUniformMatrix(camera.projection(), "projection");

		 update(anim);

		 opengl.render();


		 shader.disable();

		 SDL_GL_SwapWindow(sdl.win);

	}
}

void	ParticleSystem::update(bool anim) {
	static std::clock_t		oldTime = std::clock();
	std::clock_t			currentTime;
	cl_float				deltaTime;

		currentTime = std::clock();
		deltaTime = 1000.0f * (currentTime - oldTime) / CLOCKS_PER_SEC;
		oldTime = currentTime;

		if (anim)
		{
			cl::Kernel	kernel(opencl.program, "update");
			kernel.setArg(0, opencl.buffers[0]);
			kernel.setArg(1, opencl.buffers[1]);
			kernel.setArg(2, sizeof(cl_float4), glm::value_ptr(gravity_point));
			kernel.setArg(3, sizeof(cl_float), &deltaTime);

			glFinish();

			opencl.queue.enqueueAcquireGLObjects(&opencl.buffers);
			opencl.queue.enqueueNDRangeKernel(kernel, cl::NullRange,
					cl::NDRange(PARTICLES_AMOUNT),
					cl::NullRange);
			opencl.queue.finish();
			opencl.queue.enqueueReleaseGLObjects(&opencl.buffers);
		}
}

void	ParticleSystem::swapColorSet() {
//	float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

//	glUniform4f(shader.uniform("border_color"), srand(
}

void	ParticleSystem::screenToWorld(unsigned int x, unsigned int y) {

	float	glX = opengl.getXCoord(x);
	float	glY = opengl.getYCoord(y);

	glm::mat4	invP = glm::inverse(camera.projection() * camera.view());
	glm::vec4	screenPos = glm::vec4(glX, glY, 1.f, 1.f);
	glm::vec4	worldPos = invP * screenPos;


	gravity_point = glm::vec4(camera.position(), 1.f) + worldPos * (-camera.position().z);
	glUniform4f(shader.uniform("gravity_point"), gravity_point.x,
			gravity_point.y, 0, 0);
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

