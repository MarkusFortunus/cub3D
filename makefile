NAME		=	cub3D
O_DIRECT 	=	./bin/
SRC_DIRECT	=	src/
MY_LIBFT	=	./libft/ 
MY_PRINTF	=	./libft/ft_printf/
MLX_DIR		=	./MLX42/
MLX_LIBRARY	=	$(MLX_DIR)/build
MY_FILES	=	main.c free_err.c init.c input.c raytracing.c raytracing_utils.c parsing.c parsing_utils.c get_data.c \
check_map.c check_map2.c parsing_utils2.c
MY_SOURCES	=	$(addprefix $(SRC_DIRECT), $(MY_FILES))
MY_OBJECTS	=	$(addprefix $(O_DIRECT), $(MY_SOURCES:src/%.c=%.o))
CC			=	gcc
LIBFLAGS	=	-L$(MY_LIBFT) -lft -I$(MY_LIBFT) -L$(MY_PRINTF) -lftprintf -I$(MY_PRINTF)
MLXLIBFLAGS	=	-L./MLX42/build/ -lmlx42 -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib" -I. -framework Cocoa -framework OpenGL -framework IOKit
CCFLAGS		=  -Wall -Wextra -Werror

all:		homebrew check_dependencies init_mlx $(NAME)

check_dependencies:
	@if [ ! -x "$$(command -v cmake)" ]; then \
        echo "CMake n'est pas installé. Installation en cours..."; \
        brew install cmake; \
    else \
    echo "cmake est déjà installé."; \
    fi;    
	@if ! pkg-config --exists glfw3; then \
        echo "GLFW n'est pas installé. Installation en cours..."; \
        brew install glfw; \
    else \
    echo "GLFW est déjà installé."; \
    fi;
homebrew:
	@if [ ! -x "$$(command -v brew)" ]; then \
        echo "Homebrew n'est pas installé. Installation en cours..."; \
        /bin/bash -c "$$(curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh)"; \
    fi

init_mlx:	$(MLX_DIR)
	cd $(MLX_DIR) && \
	cmake -B build && \
	cmake --build build -j4 

$(MLX_DIR):	
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	else \
		echo "Directory $(MLX_DIR) already exists."; \
	fi

$(NAME):	$(MLX_LIBRARY) $(MY_LIBFT) $(MY_PRINTF) $(O_DIRECT) $(MY_OBJECTS)
	@make -C $(MY_LIBFT)
	@make -C $(MY_PRINTF)
	@make -C $(MLX_LIBRARY)
	@$(CC) $(CCFLAGS) -o $(NAME) $(MY_OBJECTS) $(MLXLIBFLAGS) $(LIBFLAGS)

clean:
	rm -f *.o
	rm -rf *.dSYM
	rm -f $(O_DIRECT)*.o


fclean:	clean
	rm -f $(NAME)
	rm -rf $(O_DIRECT)
	@make fclean -C $(MY_LIBFT)
	@make fclean -C $(MY_PRINTF)


$(O_DIRECT)%.o: src/%.c
	$(CC) $(CCFLAGS) -o $@ -c $<

$(O_DIRECT):
	mkdir -p -m 777 $(O_DIRECT)

re:	fclean all

.PHONY:	all clean fclean re debug init_mlx

