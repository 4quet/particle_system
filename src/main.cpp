
#include "particle_system.h"

int	main(void)
{
	try {
		ParticleSystem	ps;
		
		ps.init();
		ps.launch();
	}
	catch (std::runtime_error error) {
		printf("ERROR: %s\n", error.what());
		return (EXIT_FAILURE);
	}
	return (0);
}
