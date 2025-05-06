NAME		=	so_long

SRC			= src/so_long.c src/validate.c src/so_long_utils.c src/so_long_moves.c src/so_player_move.c src/so_long_bonus.c \
				src/valideate_helper.c src/so_bonus_utils.c
OBJ			= $(SRC:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLX_FLAGS	= -Lmlx -lmlx -lXext -lX11 -lm

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

$(LIBFT):
			make -C $(LIBFT_DIR)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ)
			make clean -C $(LIBFT_DIR)

fclean: clean
			$(RM) $(NAME)
			make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all  clean fclean re
