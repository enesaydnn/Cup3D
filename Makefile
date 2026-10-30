NAME := cub3D
CC := cc
CFLAGS := -Wall -Wextra -Werror -O2
MLX_DIR := minilibx-linux
MLX_LIB := $(MLX_DIR)/libmlx.a
BUILD_DIR := build
MANDATORY_DIR := $(BUILD_DIR)/mandatory
BONUS_DIR := $(BUILD_DIR)/bonus

SRCS := src/core/utils.c src/core/main.c src/core/graphics.c \
	src/core/cleanup.c src/core/player.c src/core/input.c \
	src/parser/parse.c src/parser/parse_elements.c src/parser/parse_color.c \
	src/parser/parse_flow.c src/parser/parse_map.c src/parser/parse_player.c \
	src/parser/parse_tiles.c src/parser/validate_map.c \
	src/render/ray.c src/render/render.c
MANDATORY_SRCS := $(wildcard src/mandatory/*.c)
BONUS_SRCS := $(wildcard src/bonus/*_bonus.c)
MANDATORY_OBJS := $(addprefix $(MANDATORY_DIR)/,$(SRCS:.c=.o) $(MANDATORY_SRCS:.c=.o))
BONUS_OBJS := $(addprefix $(BONUS_DIR)/,$(SRCS:.c=.o) $(BONUS_SRCS:.c=.o))
MANDATORY_BIN := $(MANDATORY_DIR)/$(NAME)
BONUS_BIN := $(BONUS_DIR)/$(NAME)
LDLIBS := -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

.PHONY: all bonus clean fclean re $(NAME)

all: $(NAME)

$(NAME): $(MANDATORY_BIN)
	@cmp -s $(MANDATORY_BIN) $(NAME) || cp $(MANDATORY_BIN) $(NAME)

bonus: $(BONUS_BIN)
	@cmp -s $(BONUS_BIN) $(NAME) || cp $(BONUS_BIN) $(NAME)

$(MANDATORY_BIN): $(MANDATORY_OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(MANDATORY_OBJS) $(LDLIBS) -o $@

$(BONUS_BIN): $(BONUS_OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LDLIBS) -o $@

$(MANDATORY_DIR)/%.o: %.c include/cub3d.h $(MLX_DIR)/mlx.h | $(MANDATORY_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iinclude -I$(MLX_DIR) -c $< -o $@

$(BONUS_DIR)/%.o: %.c include/cub3d.h include/cub3d_bonus.h $(MLX_DIR)/mlx.h | $(BONUS_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -DBONUS -Iinclude -I$(MLX_DIR) -c $< -o $@

$(MLX_LIB): $(MLX_DIR)/Makefile $(MLX_DIR)/mlx.h $(wildcard $(MLX_DIR)/*.c)
	$(MAKE) -C $(MLX_DIR)

$(MANDATORY_DIR) $(BONUS_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)
	@if [ -f $(MLX_DIR)/Makefile.gen ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all
