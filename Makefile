NAME		:= miniRT

SRC_DIR		:= src
LIB_DIR		:= lib

LIBFT_DIR	:= libft
MLX_DIR		:= minilibx-linux

LIBFT		:= $(LIB_DIR)/libft.a
LIBMLX		:= $(LIB_DIR)/libmlx.a

SRC			:= $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJ			:= $(SRC:.c=.o)

# TODO set correct flags
CC			:= cc
CPPFLAGS	:= -I include -I $(LIBFT_DIR) -I $(MLX_DIR) -MMD -MP -g
CFLAGS		:= -Wall -O2#-Werror -Wextra
LDFLAGS		:= -L $(LIB_DIR)
LDLIBS		:= -lft -lmlx -lXext -lX11 -lm -lz

.PHONY:	all bonus clean fclean re

all: $(NAME)

bonus: $(NAME)

$(LIBFT): $(LIB_DIR)
	$(MAKE) --directory=$(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.a $(LIB_DIR)

$(LIBMLX): $(LIB_DIR)
	$(MAKE) --directory=$(MLX_DIR)
	cp $(MLX_DIR)/libmlx.a $(LIB_DIR)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)

$(LIB_DIR):
	mkdir -p $@

# TODO clean all
clean:
	rm -v $(OBJ)
	rm -v $(OBJ:.o=.d)
	# $(MAKE) clean --directory=$(LIBFT_DIR)
	# $(MAKE) clean --directory=$(MLX_DIR)

fclean: clean
	rm $(NAME)
	# $(MAKE) fclean --directory=$(LIBFT_DIR)

re: fclean all

-include $(OBJ:.o=.d)
