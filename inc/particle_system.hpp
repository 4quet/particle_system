
#ifndef PARTICLE_SYSTEM_H
# define PARTICLE_SYSTEM_H

# define __CL_ENABLE_EXCEPTIONS

# include <OpenCL/opencl.h>
# include <OpenGL/gl3.h>
# include <SDL.h>

# include <OpenCL/cl_gl_ext.h>
# include <OpenGL/OpenGL.h>

# include <iostream>
# include <fstream>
# include <string>
# include <sstream>
# include <map>
# include <cstdlib>

# include <stdio.h>
# include <stdlib.h>

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

# include "cl.hpp"

# include "SDL.hpp"
# include "OpenGL.hpp"
# include "OpenCL.hpp"
# include "Shader.hpp"

# include "Camera.hpp"
# include "ParticleSystem.hpp"

# define MAX_EMITTED_AMOUNT	10000

# define WIN_WIDTH			1600
# define WIN_HEIGHT			1200
# define INFO_WIN_WIDTH		400
# define INFO_WIN_HEIGHT	400

# define Z_NEAR		0.1f
# define Z_FAR		1000.0f

extern int	g_ParticlesAmount;

#endif
