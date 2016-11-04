
#ifndef PARTICLE_SYSTEM_HPP
# define PARTICLE_SYSTEM_HPP

# include "particle_system.h"

class	ParticleSystem {

	private:
		SDL_Window		*win;
		SDL_GLContext	context;

		void	initSDL();

	public:
		ParticleSystem();


		~ParticleSystem();

};

#endif
