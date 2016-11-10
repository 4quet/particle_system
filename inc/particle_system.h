
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

# define PARTICLES_AMOUNT	200000

# define WIN_WIDTH	1600
# define WIN_HEIGHT	1200

# define Z_NEAR		1.0f
# define Z_FAR		100.0f



#endif
