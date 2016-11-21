/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParticleSystem.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:43:01 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/21 11:46:49 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle_system.hpp"

ParticleSystem::ParticleSystem() {
	opencl.buffers.push_back(
		cl::BufferGL(opencl.context, CL_MEM_READ_WRITE, opengl.pos_vbo, NULL)
	);
	opencl.buffers.push_back(
		cl::BufferGL(opencl.context, CL_MEM_READ_WRITE, opengl.vel_vbo, NULL)
	);

	opencl.loadCLProgram("kernels/program.cl");

	shader.addUniform("border_color");
	shader.addUniform("center_color");
	shader.addUniform("view");
	shader.addUniform("projection");
	shader.addUniform("gravity_point");
	shader.addUniform("camera_position");

	backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);
	shader.use();
	glUniform4f(shader.uniform("border_color"), 0.65, 0.2, 0.19, 1.0f);
	glUniform4f(shader.uniform("center_color"), 0.96, 0.72, 0.43, 1.0f);
	shader.disable();

	paused = true;
	step = -camera.position().z * 0.02;
	emitted = 0;
	emitters = new std::vector<glm::vec3>();

	printUsage();
}

void	ParticleSystem::init(std::string shape_to_init) {
	paused = true;
	speed = 500.0f;
	shape = shape_to_init;
	gravity_point = glm::vec3(0.0f, 0.0f, 0.0f);

	cl::Kernel	kernel(opencl.program, shape.c_str());

	kernel.setArg(0, opencl.buffers[0]);
	kernel.setArg(1, opencl.buffers[1]);
	kernel.setArg(2, g_ParticlesAmount);

	opencl.queue.enqueueAcquireGLObjects(&opencl.buffers);
	opencl.queue.enqueueNDRangeKernel(kernel,
			cl::NDRange(emitted),
			cl::NDRange(g_ParticlesAmount), cl::NullRange);
	opencl.queue.finish();
	opencl.queue.enqueueReleaseGLObjects(&opencl.buffers);
	opencl.queue.finish();
}

void	ParticleSystem::launch() {
	SDL_Event	event;
	const Uint8	*keyboardState;
	bool		quit = false;
	bool		showFPS = false;

	glm::vec3	newPos;

	Uint32		startclock = 0;
	Uint32		deltaclock = 0;
	Uint32		timer = 0;
	char		*currentFPS;

	shader.use();
	while (!quit)
	{
		startclock = SDL_GetTicks();
	   	keyboardState = SDL_GetKeyboardState(NULL);
		newPos = camera.position();

		if (keyboardState[SDL_SCANCODE_W] && newPos.z < 0)
			newPos.z += step;
		if (keyboardState[SDL_SCANCODE_S] && newPos.z > -(Z_FAR - 20.0f))
			newPos.z -= step;
		if (keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_LEFT])
			newPos.x += step;
		if (keyboardState[SDL_SCANCODE_D] || keyboardState[SDL_SCANCODE_RIGHT])
			newPos.x -= step;
		if (keyboardState[SDL_SCANCODE_UP])
			newPos.y += step;
		if (keyboardState[SDL_SCANCODE_DOWN])
			newPos.y -= step;
		if (keyboardState[SDL_SCANCODE_KP_PLUS] && speed < 2500.0f)
			speed += 10.0f;
		if (keyboardState[SDL_SCANCODE_KP_MINUS] && speed > 10.0f)
			speed -= 10.0f;

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
							paused = !paused;
							break;
						case SDLK_TAB:
							shape = (shape == "sphere") ? "cube" : "sphere";
							init(shape);
							break;
						case SDLK_RETURN:
							randomColorSet();
							break;
						case SDLK_b:
							swapBackground();
							break;
						case SDLK_r:
							init(shape);
							break;
						case SDLK_f:
							showFPS = !showFPS;
							SDL_SetWindowTitle(sdl.win, "Particle System");
							break;
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
					{
						click = true;
						paused = false;
					}
					else if (event.button.button == SDL_BUTTON_RIGHT)
						setEmitter(gravity_point);
					break;
				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT)
						click = false;
					break;
				case SDL_MOUSEMOTION:
					screenToWorld(event.motion.x, event.motion.y);
					break;
				case SDL_QUIT:
					quit = true;
					break;
			}
		 }

		 glClearColor(	backgroundColor.x,
				 		backgroundColor.y,
				 		backgroundColor.z,
						1.0f);
		 glClear(GL_COLOR_BUFFER_BIT);

		 shader.setUniformMatrix(camera.view(), "view");
		 shader.setUniformMatrix(camera.projection(), "projection");

		 update();
		 opengl.render();

		 if (showFPS == true)
		 {
			 deltaclock = SDL_GetTicks() - startclock;
			 if (deltaclock != 0)
			 {
				 currentFPS = (char *)std::to_string(1000 / deltaclock).c_str();
				 if (startclock - timer > 1000)
				 {
					timer += 1000;
					SDL_SetWindowTitle(sdl.win, currentFPS);
				 }
			 }
		 }

		 SDL_GL_SwapWindow(sdl.win);

	}
	shader.disable();
}

void	ParticleSystem::update() {
	static cl::Kernel		kernel(opencl.program, "update");
	static std::clock_t		oldTime = std::clock();
	std::clock_t			currentTime;
	cl_float				deltaTime;
	cl_uint 				clClick;

	currentTime = std::clock();
	deltaTime = speed * (currentTime - oldTime) / CLOCKS_PER_SEC;
	oldTime = currentTime;
	clClick = (click == true) ? 1 : 0;

	if (paused == false)
	{
		try {

			kernel.setArg(0, opencl.buffers[0]);
			kernel.setArg(1, opencl.buffers[1]);
			kernel.setArg(2, sizeof(cl_float3), glm::value_ptr(gravity_point));
			kernel.setArg(3, sizeof(cl_float), &deltaTime);
			kernel.setArg(4, sizeof(cl_uint), &clClick);

			opencl.queue.enqueueAcquireGLObjects(&opencl.buffers);
			opencl.queue.enqueueNDRangeKernel(kernel,
					cl::NullRange,
					cl::NDRange(MAX_EMITTED_AMOUNT + g_ParticlesAmount),
					cl::NullRange);
			opencl.queue.finish();
			opencl.queue.enqueueReleaseGLObjects(&opencl.buffers);
			opencl.queue.finish();

			if (emitters->size() > 0)
				emit();

		} catch (cl::Error & e) {
			throw std::runtime_error(e.what());
		}
	}
}

void	ParticleSystem::setEmitter(glm::vec3 position) {
	std::vector<glm::vec3>::iterator	it;
	int 								i;

	i = 0;
	for (it = emitters->begin(); it < emitters->end(); it++, i++)
	{
		if (position.x > (*it).x - step && position.x < (*it).x + step
				&& position.y > (*it).y - step && position.y < (*it).y + step)
		{
			emitters->erase(emitters->begin() + i);
			return;
		}
	}
	emitters->push_back(position);
}

void	ParticleSystem::emit() {
	static	size_t		index = 0;
	static	cl::Kernel	kernel(opencl.program, "emit");

	kernel.setArg(0, opencl.buffers[0]);
	kernel.setArg(1, opencl.buffers[1]);
	kernel.setArg(2, sizeof(cl_float3), glm::value_ptr(emitters->at(index)));

	opencl.queue.enqueueAcquireGLObjects(&opencl.buffers);
	opencl.queue.enqueueNDRangeKernel(kernel,
			cl::NDRange(emitted),
			cl::NDRange(1),
			cl::NullRange);
	opencl.queue.finish();
	opencl.queue.enqueueReleaseGLObjects(&opencl.buffers);
	opencl.queue.finish();

	emitted += 1;
	if (emitted == MAX_EMITTED_AMOUNT)
		emitted = 0;

	index += 1;
	if (index == emitters->size())
		index = 0;
}

void	ParticleSystem::randomColorSet() {
	glUniform4f(shader.uniform("border_color"),
		static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
		static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
		static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
		1.0f
	);
	glUniform4f(shader.uniform("center_color"),
		static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
		static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
		static_cast<float>(rand()) / static_cast<float>(RAND_MAX),
		1.0f
	);
}

void	ParticleSystem::swapBackground() {
	if (backgroundColor.x < 1.0f)
		backgroundColor = glm::vec3(1.0f, 1.0f, 1.0f);
	else
		backgroundColor = glm::vec3(0.0f, 0.0f, 0.0f);
}

void	ParticleSystem::screenToWorld(unsigned int x, unsigned int y) {
	float		glX;
	float		glY;
	glm::mat4	invP;
	glm::vec3	screenPos;
	glm::vec4	worldPos;

	glX = opengl.getXCoord(x);
	glY = opengl.getYCoord(y);
	invP = glm::inverse(camera.projection() * camera.view());
	screenPos = glm::vec3(glX, glY, 1.f);
   	worldPos = invP * glm::vec4(screenPos, 1.0f);

	gravity_point = camera.position() +
		glm::vec3(worldPos) * (-camera.position().z);
	gravity_point.z = 0.0f;
	glUniform3f(shader.uniform("gravity_point"), gravity_point.x,
			gravity_point.y, 0.0f);
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

void	ParticleSystem::printUsage() const {
	std::cout << "--- PARTICLE SYSTEM : " << g_ParticlesAmount << " particles ---\n";
	std::cout << "[ TAB ] - Switch between shapes (sphere or cube)\n";
	std::cout << "[  R  ] - Reset to initial shape (sphere or cube)\n\n";

	std::cout << "[ LMB ] - Hold to enable gravity point\n";
	std::cout << "[ RMB ] - Enable particles emitter\n\n";

	std::cout << "[  W  ] - Move forward\n";
	std::cout << "[  S  ] - Move backward\n";
	std::cout << "[  A  ] - Strafe left\n";
	std::cout << "[  D  ] - Strafe right\n\n";

	std::cout << "[  +  ] - Increase movement speed\n";
	std::cout << "[  -  ] - Decrease movement speed\n\n";

	std::cout << "[ RET ] - Generate random colors\n";
	std::cout << "[  B  ] - Switch background color (black or white)\n\n";

	std::cout << "[  F  ] - Toggle FPS counter in window title\n";
	std::cout << "[ SPC ] - Toggle pause\n";
	std::cout << "[ ESC ] - Quit\n";
	std::cout << "----------------------------------------\n";
}

ParticleSystem::~ParticleSystem() {
	delete emitters;
}

