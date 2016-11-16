
#include "particle_system.hpp"

int	main(void)
{
	try {
		ParticleSystem	ps;

		srand(time(NULL));
		
		ps.init("sphere");
		ps.launch();
	}
	catch (std::runtime_error error) {
		printf("ERROR: %s\n", error.what());
		return (EXIT_FAILURE);
	}
	return (0);
}
