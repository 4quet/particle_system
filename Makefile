
SRC_DIR = src/
INC_DIR = inc/
OBJ_DIR = obj/

NAME = particle_system
SRC_FILES = main.cpp\
			ParticleSystem.cpp

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ	= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.cpp=.o))

CC = clang++
CFLAGS = -Wall -Wextra -Werror

SDL_LIB = `sdl2-config --libs`
SDL_INC = `sdl2-config --cflags`
FWK = -framework OpenGL -framework OpenCL

all: $(NAME)
	@echo "\033[32m•\033[0m $(NAME) ready"

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(SDL_LIB) $(FWK) $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INC_DIR) $(SDL_INC) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all re fclean clean