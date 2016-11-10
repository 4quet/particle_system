
#include "particle_system.h"

int	main(void)
{
	try {
		ParticleSystem	ps;

		srand(time(NULL));
		
		ps.init("cube");
		ps.launch();
	}
	catch (std::runtime_error error) {
		printf("ERROR: %s\n", error.what());
		return (EXIT_FAILURE);
	}
	return (0);
}
