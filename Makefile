RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[1;33m
BLUE=\033[0;34m
ORANGE=\033[38;2;255;165;0m
NC=\033[0m

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
SRC_PATH = srcs/
OBJ_PATH = obj/
RM = rm -rf

# Détection automatique du système
UNAME_S := $(shell uname -s)

# Configuration MLX selon le système
ifeq ($(UNAME_S),Linux)
    MLX_DIR = ./minilibx-linux
    MLX_PATH = minilibx-linux/libmlx.a
    MLX = -lmlx_Linux -lXext -lX11 -lm -lz
    MLX_OBJ = -I$(MLX_DIR) -c
    MLX_LIB = -L$(MLX_DIR) -lmlx_Linux
else ifeq ($(UNAME_S),Darwin)
    MLX_DIR = ./mlx
    MLX_PATH = mlx/libmlx.a
    MLX = -lmlx -Lmlx -framework OpenGL -framework AppKit
    MLX_OBJ = -Imlx -c
    MLX_LIB = -L$(MLX_DIR) -lmlx
else
    # Configuration par défaut (essaie Linux d'abord)
    MLX_DIR = ./mlx
    MLX_PATH = mlx/libmlx.a
    MLX = -lmlx -lXext -lX11 -lm
    MLX_OBJ = -Imlx -c
    MLX_LIB = -L$(MLX_DIR) -lmlx
endif

SRC = main.c \
       init.c \
       parsing.c \
       parsing_utils.c \
       rendering.c \
	   debug.c \
       draw.c \
       events.c \
	   events_2.c \
       get_next_line.c \
       utils.c \
       utils_2.c \
	   utils_3.c \
	   split.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

OBJ		= $(SRC:.c=.o)

OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INCS	= -I ./includes/

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

# Installation automatique de MLX pour Linux
install-mlx:
	@echo "Installing MLX for your system..."
ifeq ($(UNAME_S),Linux)
	@if [ ! -d "minilibx-linux" ]; then \
		echo "Downloading minilibx-linux..."; \
		git clone https://github.com/42Paris/minilibx-linux.git; \
	fi
	@echo "Building MLX..."
	@make -C minilibx-linux
else
	@echo "macOS detected - using existing MLX"
	@if [ -d "mlx" ]; then make -C mlx; fi
endif

# Installation des dépendances système
install-deps:
	@echo "Installing system dependencies..."
ifeq ($(UNAME_S),Linux)
	@if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update && sudo apt-get install -y gcc make xorg libxext-dev libbsd-dev; \
	elif command -v yum >/dev/null 2>&1; then \
		sudo yum install -y gcc make libX11-devel libXext-devel; \
	elif command -v pacman >/dev/null 2>&1; then \
		sudo pacman -S gcc make libx11 libxext; \
	else \
		echo "Please install manually: gcc make libx11-dev libxext-dev"; \
	fi
else
	@echo "macOS detected - no additional dependencies needed"
endif

$(NAME): $(OBJ_PATH) $(OBJS)
	@if [ ! -f "$(MLX_PATH)" ]; then \
		echo "MLX not found. Installing..."; \
		$(MAKE) install-mlx; \
	fi
	@make -C $(MLX_DIR)
	@printf " \r"
	@echo " "
	@echo "\033[0;34m ███████╗ ██████╗ ███████╗ "
	@echo "\033[0;34m ██╔════╝ ██╔══██╗ ██╔════╝ "
	@echo "\033[0;34m █████╗   ██║  ██║ █████╗   "
	@echo "\033[0;34m ██╔══╝   ██║  ██║ ██╔══╝   "
	@echo "\033[0;34m ██║      ██████╔╝ ██║      "
	@echo "\033[0;34m ╚═╝      ╚═════╝  ╚═╝      "
	@echo " "
	@$(CC) $(OBJS) $(CFLAGS) -g $(MLX_LIB) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean : clean
	@$(RM) fdf
	@echo "It's a clean!                        "
	@echo "\033[95;1m	            ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓             "
	@echo "\033[95;1m	          ▓▓▓▓▓▓▓▓▓▒▒▒▒███▓▓▓▓▓▓▓▓        "
	@echo "\033[95;1m		██▒▒████▒▒▒▒▒▒▒███▒▒▒           "
	@echo "\033[95;1m		██▒▒▒█████▒▒▒▒▒▒▒▒██▒▒▒▒▒▒▒▒    "
	@echo "\033[95;1m		█████▒▒▒▒▒▒▒▒▒▒███████████      "
	@echo "\033[95;1m		     ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒          "
	@echo "\033[95;1m     	          █████▓▓██████▓▓██           "
	@echo "\033[95;1m	       ████████▓▓██████▓▓███████       "
	@echo "\033[95;1m	    ███████████▓▓██████▓▓██████████     "
	@echo "\033[95;1m	    ▒▒▒▒▒▓█████▓▓▓▓▓▓▓▓▓▓█████▒▒▒▒▒     "
	@echo "\033[95;1m	    ▒▒▒▒▒▒▒▓▓▓░░▓▓▓▓▓▓▓░░▓▓▓▒▒▒▒▒▒▒     "
	@echo "\033[95;1m	         ▓▓▓▓▓▓▓▓     ▓▓▓▓▓▓▓▓           "
	@echo "\033[95;1m	       ███████           ███████       "
	@echo "\033[95;1m	    ██████████           ██████████     "
	@echo "                                     "

clean:
	@$(RM) $(OBJ_PATH)
	@if [ -d "$(MLX_DIR)" ]; then make clean -C $(MLX_DIR); fi

re: fclean all

# Aide pour l'utilisateur
help:
	@echo "Available targets:"
	@echo "  all         - Build the program"
	@echo "  clean       - Remove object files"  
	@echo "  fclean      - Remove object files and executable"
	@echo "  re          - Clean and rebuild"
	@echo "  install-deps- Install system dependencies (Linux)"
	@echo "  install-mlx - Download and build MLX (Linux)"
	@echo "  help        - Show this help"

.PHONY: all clean fclean re install-deps install-mlx help