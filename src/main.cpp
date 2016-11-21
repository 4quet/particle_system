
#include "particle_system.hpp"

int	g_ParticlesAmount;

void	setParticlesAmount(int amount)
{
	g_ParticlesAmount = amount;
	if (amount < 100)
		g_ParticlesAmount = 100;
	else if (amount > 5000000)
		g_ParticlesAmount = 5000000;
}

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("usage: ./particle_system <amount> [100 - 5000000]\n");
		return (EXIT_FAILURE);
	}
	try {
		srand(time(NULL));

		setParticlesAmount(atoi(argv[1]));
		ParticleSystem	ps;
		
		ps.init("sphere");
		ps.launch();
	}
	catch (std::runtime_error error) {
		printf("ERROR: %s\n", error.what());
		return (EXIT_FAILURE);
	}
	return (0);
}
