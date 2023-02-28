#########################
#		VARIABLES		#
#########################

# Folders and names
NAME			:=	cub3D

HEADERS_DIR		:=	inc
HEADERS_FILES	:=	cub3d.h \
					mlx_utils.h

HEADERS			:= $(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))

SRC_DIR			:=	src
SRC_FILES		:=	main.c \
					parsing.c \
					find_texture_path_and_get_color.c \
					maze_validity_checking.c \
					utils.c \
					mlx_init.c \
					mlx_hooks.c \
					mlx_utils.c

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

LIB_NAMES		:=	lib/libft
LIBS			=	$(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD			=	$(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS		=	$(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS		=	$(foreach lib,$(LIB_NAMES),-I$(lib)/inc/)

LIB_PATHS		+=	lib/minilibx-linux/libmlx_Linux.a \
					lib/minilibx-linux/libmlx.a
LIB_HEADERS		+= -Ilib/minilibx-linux
LIBS			+= -lmlx_Linux -lX11 -lXext -lz -lmlx  -lm#-lmlx -,
LIB_LD			+= -Llib/minilibx-linux

BUILD_DIR		:=	build
OBJS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.o)
DEPS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.d)
CCDEFS			:=	NAME=\"$(NAME)\"

# Compiler options
CC				:=	cc
DEBUG_FLAG		:=	-g3
CC_FLAGS		:=	-Wextra -Werror -Wall -O3 $(DEBUG_FLAG)
CC_DEPS_FLAGS	:=	-MP -MMD
CC_DEFS_FLAGS	:=	$(foreach def,$(CCDEFS),-D $(def))

MAKE			:=	make -C

# define standard colors
_END			:=	\x1b[0m
_BOLD			:=	\x1b[1m
_UNDER			:=	\x1b[4m
_REV			:=	\x1b[7m
_GREY			:=	\x1b[30m
_RED			:=	\x1b[31m
_GREEN			:=	\x1b[32m
_YELLOW			:=	\x1b[33m
_BLUE			:=	\x1b[34m
_PURPLE			:=	\x1b[35m
_CYAN			:=	\x1b[36m
_WHITE			:=	\x1b[37m

#########################
# 		RULES			#
#########################

all: $(NAME)

$(LIB_PATHS): force
	@$(foreach lib, $(LIB_NAMES), \
		$(MAKE) $(lib); \
	)

$(NAME): $(LIB_PATHS) $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) $(LIB_LD) $(LIBS) -o $@ 

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_PATHS) Makefile
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) $(CC_DEPS_FLAGS) $(CC_DEFS_FLAGS) -I$(HEADERS_DIR) $(LIB_HEADERS) -c $< -o $@

clean:
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib) clean; \
	)
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DIR_B)

fclean: clean
	@$(foreach lib, $(LIB_NAMES), \
		@$(MAKE) $(lib) fclean; \
	)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re force
