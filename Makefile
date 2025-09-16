NAME = cube_3d

SRCDIR = src
OBJDIR = obj
INCDIR = include

# Source Files
SRC = main.c \
		init/init_map.c \
		init/init_player.c \
		init/init_ray.c \
		parsing/parsing.c \
		parsing/parse_input.c \
		parsing/parse_params.c \
		parsing/parse_map.c \
		parsing/check_map.c \
		parsing/check_textures.c \
		raycasting/raycasting.c \
		raycasting/loads_textures.c \
		utils/utils_print.c \
		utils/utils_parsing.c \
		utils/utils_free_struct.c \
		utils/utils_raycasting.c \
		event/keys.c \
		event/move.c \
		event/movement.c
	 
OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

# Libft - Please configure your own path if different
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)#/include 		#Your header file in include dir ?
# MiniLibx -> Please include in header file: #include "mlx.h"
MINILIBX_DIR := ./minilibx-linux
MLX := $(MINILIBX_DIR)/libmlx.a
# Libraries and Linker Flags
LDFLAGS =  -L$(MINILIBX_DIR) -L$(LIBFT_DIR)
LIBS =  $(MLX) $(LIBFT)

# Archiver
AR = ar
ARFLAGS = rcs

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3 -I$(MINILIBX_DIR) -I/usr/include/X11 -I$(LIBFT_INCLUDE) #/-fsanitize=address

# Detect OS for Flags MiniLibx
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLXFLAGS += -lmlx -lXext -lX11
else ifeq ($(UNAME_S),Darwin)
	MLXFLAGS += -L/opt/X11/lib -lX11 -lXext -lXrandr -lXcursor
endif


# Compilation mode (silent by default, set VERBOSE=1 to show commands)
VERBOSE ?= 0
ifeq ($(VERBOSE),1)
  V := 
else
  V := @
endif

# Colors
RED     := "\033[1;31m"
GREEN   := "\033[1;32m"
RESET   := "\033[0m"



# Default Rule
all: $(OBJDIR) $(MINILIBX_DIR) $(LIBFT) $(NAME)

# Object Directory Rule
$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

# Dependency Files
DEP = $(OBJ:.o=.d)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

# Linking Rule
$(NAME): $(OBJ) $(LIBFT)
	$(V)$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(BONUS_OBJ) $(LIBS) $(MLXFLAGS) -o $(NAME) -lm
	$(V)echo $(GREEN)"[$(NAME)] Executable created ✅"$(RESET)

# Libft
$(LIBFT):
	$(V)$(MAKE) --silent -C $(LIBFT_DIR)
	$(V)echo '[$(NAME)] Libft build successfully'

# MiniLibX
$(MINILIBX_DIR):
	$(V)echo '[$(NAME)] Downloading MiniLibX from github.com...'$(RESET)
	@git clone https://github.com/42Paris/minilibx-linux.git $(MINILIBX_DIR) > /dev/null 2>&1
	$(V)echo '[$(NAME)] Compiling MiniLibX...'$(RESET)
	@$(MAKE) -C $(MINILIBX_DIR) > /dev/null 2>&1
	$(V)echo '[$(NAME)] MiniLibX installed successfully'$(RESET)

# Clean Rules
clean:
	$(V)echo $(RED)'[$(NAME)] Cleaning objects'd$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(NAME)
	$(V)$(MAKE) --silent -C $(LIBFT_DIR) fclean
	$(V)echo $(RED)'[mlx] Remove directory'$(RESET)
	@rm -rf $(MINILIBX_DIR)

re: fclean all

# Makefile Reconfiguration 
regen:
	makemyfile

.PHONY: all clean fclean re bonus regen
.DEFAULT_GOAL := all
