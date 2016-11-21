/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfourque <lfourque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 08:42:01 by lfourque          #+#    #+#             */
/*   Updated: 2016/11/21 10:56:12 by lfourque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particle_system.hpp"

SDL::SDL() {
	initOpenGLWindow();
}

void	SDL::initOpenGLWindow() {
	std::string	errorMsg;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		errorMsg = SDL_GetError();
		SDL_Quit();
		throw std::runtime_error(errorMsg);
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	win = SDL_CreateWindow("Particle System", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if (win == 0)
	{
		errorMsg = SDL_GetError();
		SDL_Quit();
		throw std::runtime_error(errorMsg);
	}

	context = SDL_GL_CreateContext(win);
	if (context == 0)
	{
		errorMsg = SDL_GetError();
		SDL_DestroyWindow(win);
		SDL_Quit();
		throw std::runtime_error(errorMsg);
	}
}

SDL::~SDL() {
	SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
	SDL_Quit();
}
