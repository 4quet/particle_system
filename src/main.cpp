
#include "particle_system.h"

int	main(void)
{
	try {
		ParticleSystem	ps;
	}
	catch (std::runtime_error error) {
		printf("ERROR: %s\n", error.what());
		return (EXIT_FAILURE);
	}
	return (0);
}
